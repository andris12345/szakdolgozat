#include <iostream>
#include <ostream>
#include <cstdio>
#include <string>
#include <filesystem>
#include <format>
#include <thread>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3_net/SDL_net.h>
#include <SDL3_image/SDL_image.h>

#include "source/gui/felirat/Felirat.h"
#include "source/variables/Variables.h"
#include "source/variables/AiVariables.h"
#include "source/unit/create/CreateMan.h"
#include "source/unit/fighter/Fighter.h"
#include "source/unit/move/MoveMan.h"
#include "source/unit/ranged/Ranged.h"
#include "source/unit/tank/Tank.h"
#include "source/ai/easy/easyAi.h"
#include "source/ai/medium/mediumAi.h"
#include "source/ai/hard/hardAi.h"
#include "source/MultiPlayer/multiPlayer.h"

const int FRAME_DELAY = 1000 / TARGET_FPS; // Ennyi ms kell egy frame-hez (1000ms / 60fps = 16.67ms)

SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) == false){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't initialize SDL!", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << SDL_GetError() << std::endl;
    }
    font = TTF_OpenFont("../../assets/albert-text/AlbertText-Bold.ttf", fontSize);
    gombFont = TTF_OpenFont("../../assets/albert-text/AlbertText-Bold.ttf", 30);
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << SDL_GetError() << std::endl;
    }

    // 800x450 is 16:9
    if (SDL_CreateWindowAndRenderer("Game", width, height, 0, &window, &renderer) == false){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't create window/renderer!", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    SDL_Surface* tempSurface = nullptr;

    tempSurface = IMG_Load("D:/CLion/szakdolgozat/source/images/roguelikeChar_transparent_596.png");
    if (tempSurface) {
        fighterBodyTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_DestroySurface(tempSurface);
    }else {
        SDL_Log("Failed to load image! SDL Error: %s", SDL_GetError());
    }

    // Fighter weapon
    tempSurface = IMG_Load("D:/CLion/szakdolgozat/source/images/roguelikeChar_transparent_369.png");
    if (tempSurface) {
        fighterWeaponTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_DestroySurface(tempSurface);
    }

    // Ranged body
    tempSurface = IMG_Load("D:/CLion/szakdolgozat/source/images/roguelikeChar_transparent_326.png");
    if (tempSurface) {
        rangedBodyTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_DestroySurface(tempSurface);
    }

    // ranged weapon
    tempSurface = IMG_Load("D:/CLion/szakdolgozat/source/images/roguelikeChar_transparent_107.png");
    if (tempSurface) {
        rangedWeaponTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_DestroySurface(tempSurface);
    }

    // tank unit
    tempSurface = IMG_Load("D:/CLion/szakdolgozat/source/images/roguelikeChar_transparent_595.png");
    if (tempSurface) {
        tankUnitTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_DestroySurface(tempSurface);
    }

    penzText = new Subtitle(font, fontColor, SDL_FRect{50, 20, 0, 0});
    xpText = new Subtitle(font, fontColor, SDL_FRect{170, 20, 0, 0});
    endText = new Subtitle(gombFont, fontColor, SDL_FRect{350, 200, 0, 0});
    //todo: gombokbol kirakni a meseszamokat ha lehet
    fighterBt =         new Gomb({320, 10, 150, 50},  {0, 255, 0, 255}, {0, 90, 0, 255}, "Fighter: 10.0", gombFont);
    rangedBt =          new Gomb({480, 10, 150, 50},  {0, 255, 0, 255}, {0, 90, 0, 255}, "Ranged: 15", gombFont);
    tankBt =            new Gomb({640, 10, 150, 50},  {0, 255, 0, 255}, {0, 90, 0, 255}, "Tank: 20", gombFont);
    singlePlayerBT =    new Gomb({350, 100, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "single player", gombFont);
    multiPlayerBt =     new Gomb({350, 200, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "multi player", gombFont);
    exitBt =            new Gomb({350, 300, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "exit", gombFont);
    easyBt =            new Gomb({350, 100, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "easy", gombFont);
    mediumBt =          new Gomb({350, 200, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "medium", gombFont);
    hardBt =            new Gomb({350, 300, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "hard", gombFont);
    mainMenuBt =        new Gomb({350, 300, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "Main Menu", gombFont);
    tower1Holder =      new Gomb({(behuzasi_tavolsag - 50), (emberKezdoY - 100), 30, 30},{137, 81, 41, 255}, {98, 58, 29, 255}, "+", gombFont);
    tower2Holder =      new Gomb({(behuzasi_tavolsag - 50), (emberKezdoY - 70), 30, 30},{137, 81, 41, 255}, {98, 58, 29, 255}, "+", gombFont);
    tower1Bt =          new Gomb({(behuzasi_tavolsag - 10), (emberKezdoY - 100), 65, 20},{255,165,0, 255}, {255,140,0, 255}, "Tower 1 10", font);
    tower2Bt =          new Gomb({(behuzasi_tavolsag - 10), (emberKezdoY - 70), 65, 20},{255,165,0, 255}, {255,140,0, 255}, "Tower 2 10", font);
    deleteBt =          new Gomb({(behuzasi_tavolsag - 10), (emberKezdoY - 70), 40, 20},{255,165,0, 255}, {255,140,0, 255}, "Delete", font);
    levelUpBt =         new Gomb({250, 20, 40, 20},{0, 255, 0, 255}, {0, 90, 0, 255}, "Level up", font);
    hostBt =            new Gomb({350, 100, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "Host game", gombFont);
    joinBt =            new Gomb({350, 200, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "Join game", gombFont);
    backBt =            new Gomb({700, 10, 80, 50}, {0, 255, 0, 255}, {0, 90, 0, 255}, "Back", gombFont);

    kocka.h = kocka.w = 20;

    if (InitializeNetworking()) {
        std::cout << "Initializing networking..." << std::endl;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_EVENT_QUIT:
                return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            if (event->key.key == SDLK_ESCAPE)
            {
                return SDL_APP_SUCCESS;
            }
        case SDL_EVENT_MOUSE_BUTTON_DOWN :{
            float x, y;
            SDL_GetMouseState(&x, &y);

            if (event->button.button == SDL_BUTTON_LEFT) {
                if (singlePlayerBT->getIsVisible() && isMouseOver(singlePlayerBT, x, y)) {
                SDL_Log("meg van nyomva: singlePlayerBT");
                singlePlayer = true;
                fomenu = false;
                singlePlayerBT->setIsVisible(false);
                }
                if (easyBt->getIsVisible() && isMouseOver(easyBt, x, y)) {
                    SDL_Log("meg van nyomva: easyBT");
                    dificulty = 1;
                    start = true;
                    bot = true;
                    easyBt->setIsVisible(false);
                    mediumBt->setIsVisible(false);
                    hardBt->setIsVisible(false);
                }else  if (mediumBt->getIsVisible() && isMouseOver(mediumBt, x, y)) {
                    SDL_Log("meg van nyomva: mediumBT");
                    dificulty = 2;
                    start = true;
                    bot = true;
                    easyBt->setIsVisible(false);
                    mediumBt->setIsVisible(false);
                    hardBt->setIsVisible(false);
                }else if (hardBt->getIsVisible() && isMouseOver(hardBt, x, y)) {
                    SDL_Log("meg van nyomva: hardBT");
                    dificulty = 3;
                    start = true;
                    bot = true;
                    easyBt->setIsVisible(false);
                    mediumBt->setIsVisible(false);
                    hardBt->setIsVisible(false);
                }else if (fighterBt->getIsVisible() && isMouseOver(fighterBt, x, y)) {
                    Fighter fighter = Fighter(0, (12 + (12 * player1.getLevel() * 0.25)),(2 + (2 * player1.getLevel() * 0.25)), false);
                    if (client && player2.getMoney() >= (10 + 10 * player2.getLevel() * 0.25)) {
                        ClientSpawnUnit(0);
                    }else {
                        fighter.setPrice(10 + 10 * player1.getLevel() * 0.25);
                        //fighter.setXp(10 + 10 * player1.getLevel() * 0.25);
                        fighter.setXp(100);
                        if (player1.getMoney() >= fighter.getPrice()) {
                            player1.setMoney(player1.getMoney() - fighter.getPrice());
                            CreateManToPool(fighter, false);
                        }
                    }
                }else if (rangedBt->getIsVisible() && isMouseOver(rangedBt, x, y)) {
                    Ranged ranged = Ranged(1, (8 + (8 * player1.getLevel() * 0.25)), (2 + (2 * player1.getLevel() * 0.25)), false);
                    if (client && player2.getMoney() >= (15 + 15 * player2.getLevel() * 0.25)) {
                        ClientSpawnUnit(1);
                    }else {
                        ranged.setPrice(15 + 15 * player1.getLevel() * 0.25);
                        ranged.setXp(10 + 10 * player1.getLevel() * 0.25);
                        if (player1.getMoney() >= ranged.getPrice()) {
                            player1.setMoney(player1.getMoney() - ranged.getPrice());
                            CreateManToPool(ranged, false);
                        }
                    }
                }else if (tankBt->getIsVisible() && isMouseOver(tankBt, x, y)) {
                    Tank tank = Tank(2, (16 + (16 * player1.getLevel() * 0.25)), (2 + (2 * player1.getLevel() * 0.25)), false);
                    if (client && player2.getMoney() >= (20 + 20 * player2.getLevel() * 0.25)) {
                        ClientSpawnUnit(2);
                    }else {
                        tank.setPrice(20 + 20 * player1.getLevel() * 0.25);
                        tank.setXp(20 + 20 * player1.getLevel() * 0.25);
                        if (player1.getMoney() >= tank.getPrice()) {
                            player1.setMoney(player1.getMoney() - tank.getPrice());
                            CreateManToPool(tank, false);
                        }
                    }
                }else if (mainMenuBt->getIsVisible() && isMouseOver(mainMenuBt, x, y)) {
                    fomenu = true;
                    start = false;
                    vegeMenu = false;
                    singlePlayer = false;
                    mainMenuBt->setIsVisible(false);
                    hostBt->setIsVisible(false);
                    joinBt->setIsVisible(false);
                    multiPlayer = false;
                }else if (tower1Bt->getIsVisible() && isMouseOver(tower1Bt, x, y)) {
                    if (client && player1.getMoney() >= tower1Cost) {
                        if (pos == 0) {
                            tower1Holder->setIsVisible(false);
                        }else {
                            tower2Holder->setIsVisible(false);
                        }
                        ClientBuyTower(1, pos);
                    }else if (player1.getMoney() >= tower1Cost) {
                        player1.setMoney(player1.getMoney() - tower1Cost);
                        if (pos == 0) {
                            tower1Holder->setIsVisible(false);
                        }else {
                            tower2Holder->setIsVisible(false);
                        }
                        CreateNewTower(1, pos, false);
                        buyTower = false;
                    }
                    buyTower = false;
                }else if (tower2Bt->getIsVisible() && isMouseOver(tower2Bt, x, y)) {
                    if (client && player1.getMoney() >= tower2Cost) {
                        if (pos == 0) {
                            tower1Holder->setIsVisible(false);
                        }else {
                            tower2Holder->setIsVisible(false);
                        }
                        ClientBuyTower(2, pos);
                    }else if (player1.getMoney() >= tower2Cost) {
                        player1.setMoney(player1.getMoney() - tower2Cost);
                        if (pos == 0) {
                            tower1Holder->setIsVisible(false);
                        }else {
                            tower2Holder->setIsVisible(false);
                        }
                        CreateNewTower(2, pos, false);
                        buyTower = false;
                    }
                    buyTower = false;
                }else if (deleteBt->getIsVisible() && isMouseOver(deleteBt, x, y)) {
                    if (client) {
                        ClientDeleteTower(deleteTowerNumber);
                        deleteBt->setIsVisible(false);
                    }else {
                        player1.setMoney(player1.getMoney() + (player1.getTowerAt(deleteTowerNumber)->getCost()/2));
                        player1.getTowerAt(deleteTowerNumber)->resetTower();
                        deleteBt->setIsVisible(false);
                    }

                }else if (levelUpBt->getIsVisible() && isMouseOver(levelUpBt, x, y)) {
                    levelUp(false);
                    player1.setXp(player1.getXp() - 100);
                    levelUpBt->setIsVisible(false);
                }else if (multiPlayerBt->getIsVisible() && isMouseOver(multiPlayerBt, x, y)) {
                    multiPlayer = true;
                    fomenu = false;
                    singlePlayerBT->setIsVisible(false);
                    multiPlayerBt->setIsVisible(false);
                    exitBt->setIsVisible(false);
                }else if (exitBt->getIsVisible() && isMouseOver(exitBt, x, y)) {
                    return SDL_APP_SUCCESS;
                }else if (hostBt->getIsVisible() && isMouseOver(hostBt, x, y)) {
                    SDL_Log("Host game gomb megnyomva!");
                    multiPlayer = false;
                    hostBt->setIsVisible(false);
                    joinBt->setIsVisible(false);
                    backBt->setIsVisible(false);

                    // Szerver indítása KÜLÖN SZÁLON (nem blokkoló!)
                    if (StartServerAsync()) {
                        SDL_Log("Szerver indítása elkezdődött!");
                    } else {
                        SDL_Log("Szerver indítása sikertelen!");
                    }

                }else if (joinBt->getIsVisible() && isMouseOver(joinBt, x, y)) {
                    SDL_Log("Join game gomb megnyomva!");
                    multiPlayer = false;
                    hostBt->setIsVisible(false);
                    joinBt->setIsVisible(false);
                    backBt->setIsVisible(false);

                    // Csatlakozás szerverhez
                    if (ConnectToServer("127.0.0.1")) {
                        SDL_Log("Sikeres csatlakozás!");
                        client = true;
                        start = true;
                    } else {
                        SDL_Log("Csatlakozás sikertelen!");
                        multiPlayer = true;
                    }


                }   else if (backBt->getIsVisible() && isMouseOver(backBt, x, y)) {
                    if (singlePlayer && !start) {
                        singlePlayer = false;
                        fomenu = true;
                        easyBt->setIsVisible(false);
                        mediumBt->setIsVisible(false);
                        hardBt->setIsVisible(false);
                        backBt->setIsVisible(false);
                    }else if (multiPlayer && !start){
                        fomenu = true;
                        start = false;
                        vegeMenu = false;
                        singlePlayer = false;
                        hostBt->setIsVisible(false);
                        joinBt->setIsVisible(false);
                        backBt->setIsVisible(false);
                        multiPlayer = false;
                    }else if (waitingForPlayer && !start) {
                        waitingForPlayer = false;
                        fomenu = false;
                        start = false;
                        vegeMenu = false;
                        singlePlayer = false;
                        multiPlayer = true;
                        g_network.isServer = false;
                    }
                }
                else {
                    buyTower = false; //todo: valahogz megcsinalni hogy ne mindig ugyan ugy jelenjen meg a towervasarlas
                    tower1Bt->setIsVisible(false);
                    tower2Bt->setIsVisible(false);
                    deleteBt->setIsVisible(false);
                }
            }


            if (event->button.button == SDL_BUTTON_RIGHT) {
                if (tower1Holder->getIsVisible() && isMouseOver(tower1Holder, x, y)) {
                    buyTower = true;
                    pos = 0;
                }else if (tower2Holder->getIsVisible() && isMouseOver(tower2Holder, x, y)) {
                    buyTower = true;
                    pos = 1;
                }else if (player1.getTowerAt(0)->isExists() && isMouseOver(player1.getTowerAt(0), x, y)) {
                    deleteBt->setIsVisible(true);
                    deleteTowerNumber = 0;
                }else if (player1.getTowerAt(1)->isExists() && isMouseOver(player1.getTowerAt(1), x, y)) {
                    deleteBt->setIsVisible(true);
                    deleteTowerNumber = 1;
                }
                else {
                    buyTower = false;
                    tower1Bt->setIsVisible(false);
                    tower2Bt->setIsVisible(false);
                    deleteBt->setIsVisible(false);
                }
            }
        }
        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    frameStart = SDL_GetTicks();

    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    if (fomenu) {
        render_Button(singlePlayerBT);
        render_Button(multiPlayerBt);
        render_Button(exitBt);
    }
    if (singlePlayer && !start) {
        render_Button(easyBt);
        render_Button(mediumBt);
        render_Button(hardBt);
        render_Button(backBt);
    }
    if (multiPlayer && !start) {
        render_Button(hostBt);
        render_Button(joinBt);
        render_Button(backBt);
    }
    if (waitingForPlayer) {
        render_Button(backBt);
    }

    if (vege) {
        if (player1.getBaseHp() <= 0) {
            endText->setText("Vege sajnos te vesztettel!");
        }else {
            endText->setText("Vege te nyertel!");
        }

        if (client) {
            if (g_network.clientSocket) {
                NET_DestroyStreamSocket(g_network.clientSocket);
                g_network.clientSocket = nullptr;
                g_network.isConnected = false;
            }
        }

        start = false;
        singlePlayer = false;
        client = false;
        server = false;

        fighterBt->setIsVisible(false);
        rangedBt->setIsVisible(false);
        tankBt->setIsVisible(false);

        player1.setBaseHp(maxBaseHp);
        player2.setBaseHp(maxEnemybaseHp); //todo megcsinalni a veget is a nullazasok

        player1.resetUser();
        player2.resetUser();

        unitCounter = 0;

        vegeMenu = true;
        vege = false;

        for (int i = 0; i < mezoszam; i++) {
            map[i] = 0;
        }
    }

    if (vegeMenu) {
        endText->render();
        render_Button(mainMenuBt);
    }



    if (start) {
        if (server) {
            player2.setMoney(player2.getMoney() + 1/30.0);
        }
        if (client) {
            if (player1.getTowerAt(0)->isExists()) {
                SDL_Log("Tower 1 exists!");
            }
            UpdateNetworking();  // Automatikus szinkronizáció
            if (player1.getTowerAt(0)->isExists()) {
                SDL_Log("Tower 1 exists!");
            }

            SDL_FRect vonal = {.x = 300 , .y = 200-emberszelesseg/2, .w = 1, .h = emberszelesseg + emberszelesseg};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &vonal);
            for (int i = 0; i <= mezoszam; i++) {
                SDL_FRect rect = {.x = (mezoszelesseg * i) + behuzasi_tavolsag , .y = 200-emberszelesseg/2, .w = 1, .h = emberszelesseg + emberszelesseg/2};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }



            // Gombok
            fighterBt->getSubtitle()->setText("Fighter: " + std::format("{:.1f}",(10 + 10 * player1.getLevel() * 0.25)));
            rangedBt->getSubtitle()->setText("Ranged: " + std::format("{:.1f}",(15 + 15 * player1.getLevel() * 0.25)));
            tankBt->getSubtitle()->setText("Tank: " +  std::format("{:.1f}",(20 + 20 * player1.getLevel() * 0.25)));
            render_Button(fighterBt);
            render_Button(rangedBt);
            render_Button(tankBt);

            // UI (a money és xp már frissítve van a szerver állapotból)
            std::string text = "Pénz: " + std::format("{:.1f}", player1.getMoney());
            penzText->setText(text);
            penzText->render();

            // XP bar
            float ratio = player1.getXp() / 100.0f;
            float xpWidth = std::min((ratio * 125), 125.0f);
            SDL_FRect rect = {120, 20, 125, 20};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
            rect = {120, 20, xpWidth, 20};
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &rect);

            text = std::to_string((int)player1.getXp()) + "/100";
            xpText->setText(text);
            xpText->render();

            basekirajzolas(renderer);
            unitKirajzolas(renderer);
            hpKirajzolasHelper();
            toronyKirajzolas(renderer);

        }else if (bot){
            if (player2.getXp() >= 100) {
                player2.setXp(player2.getXp() - 100);
                player2.setLevel(player2.getLevel() + 1);
            }
            switch (dificulty) {
                case 1: {
                    easyAi();
                    break;
                }
                case 2: {
                    mediumAi();
                    break;
                }
                case 3: {
                    hardAi();
                    break;
                }
                default:
                    break;
            }
        }
        if (!client) {
            player1.setMoney(player1.getMoney() + 1/30.0);
            std::string text = "Pénz: " + std::format("{:.1f}", player1.getMoney());

            penzText->setText(text);
            penzText->render();


            if (buyTower) {
                render_Button(tower1Bt);
                render_Button(tower2Bt);
            }else {
                tower1Bt->setIsVisible(false);
                tower2Bt->setIsVisible(false);
            }

            if (deleteBt->getIsVisible()) {
                render_Button(deleteBt);
            }

            Move(renderer);

            if (!player1.getTowerAt(0)->isExists()) {
                render_Button(tower1Holder);
            }
            if (!player1.getTowerAt(1)->isExists()) {
                render_Button(tower2Holder);
            }

            for (int i = 0; i < 2; i++) {
                if (!player1.getTowerAt(i)->isExists()) {
                    continue;
                }
                if (player1.getTowerAt(i)->getIsVisible()) {
                    renderTower(renderer, *player1.getTowerAt(i));
                }
            }

            //xp kirajzolas:
            float ratio = player1.getXp() / static_cast<float>(100);
            float xpWidth = std::min((ratio * 125), static_cast<float>(125));
            SDL_FRect rect = {.x = 120, .y = 20, .w = 125, .h = 20};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);

            rect = {.x = 120, .y = 20, .w = xpWidth, .h = 20};
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &rect);

            text = std::to_string(static_cast<int>(player1.getXp())) + "/100";

            xpText->setText(text);
            xpText->render();
            toronyKirajzolas(renderer);

            if (ratio >= 1) {
                render_Button(levelUpBt);
            }
        }
    }

    SDL_RenderPresent(renderer);



    //fix fps
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY) {
        SDL_Delay(FRAME_DELAY - frameTime);
        frameSzamlalo++;
        if (frameSzamlalo % 30 == 0) {
            frameSzamlalo = 0;
        }
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    CleanupNetworking();
    // Gombok
    delete fighterBt;
    delete rangedBt;
    delete tankBt;
    delete singlePlayerBT;
    delete easyBt;
    delete mediumBt;
    delete hardBt;
    delete mainMenuBt;
    delete tower1Holder;
    delete tower2Holder;
    delete tower1Bt;
    delete tower2Bt;
    delete deleteBt;
    delete backBt;

    // Szövegek
    delete penzText;
    delete endText;
    delete xpText;

    // SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Fontok
    TTF_CloseFont(font);
    TTF_CloseFont(gombFont);

    TTF_Quit();
    SDL_Quit();
}