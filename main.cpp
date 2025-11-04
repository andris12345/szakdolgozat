#include <iostream>
#include <ostream>
#include <cstdio>
#include <string>
#include <filesystem>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>

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
    if (SDL_CreateWindowAndRenderer("hello SDL3", width, height, 0, &window, &renderer) == false){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't create window/renderer!", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    penzText = new Subtitle(font, fontColor, SDL_FRect{100, 20, 0, 0});
    xpText = new Subtitle(font, fontColor, SDL_FRect{240, 20, 0, 0});
    endText = new Subtitle(gombFont, fontColor, SDL_FRect{350, 200, 0, 0});
    //todo: gombokbol kirakni a meseszamokat ha lehet
    fighterBt = new Gomb({470, 10, 100, 50}, {0, 255, 0, 255}, {0, 90, 0, 255}, "Fighter", gombFont);
    rangedBt = new Gomb({580, 10, 100, 50}, {0, 255, 0, 255}, {0, 90, 0, 255}, "Ranged", gombFont);
    tankBt = new Gomb({690, 10, 100, 50}, {0, 255, 0, 255}, {0, 90, 0, 255}, "Tank", gombFont);
    singlePlayerBT = new Gomb({350, 100, 100, 80}, {0, 255, 0, 255}, {0, 90, 0, 255},"single player", gombFont);
    easyBt = new Gomb({350, 100, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "easy", gombFont);
    mediumBt = new Gomb({350, 200, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "medium", gombFont);
    hardBt = new Gomb({350, 300, 200, 80}, {0, 255, 0, 255}, {0, 90, 0, 255}, "hard", gombFont);
    mainMenuBt = new Gomb({350, 300, 200, 80},{0, 255, 0, 255}, {0, 90, 0, 255}, "Main Menu", gombFont);
    tower1Holder = new Gomb({(behuzasi_tavolsag - 50), (emberKezdoY - 100), 30, 30},{137, 81, 41, 255}, {98, 58, 29, 255}, "+", gombFont);
    tower2Holder = new Gomb({(behuzasi_tavolsag - 50), (emberKezdoY - 70), 30, 30},{137, 81, 41, 255}, {98, 58, 29, 255}, "+", gombFont);
    tower1Bt = new Gomb({(behuzasi_tavolsag - 10), (emberKezdoY - 100), 40, 20},{255,165,0, 255}, {255,140,0, 255}, "Tower 1", font);
    tower2Bt = new Gomb({(behuzasi_tavolsag - 10), (emberKezdoY - 70), 40, 20},{255,165,0, 255}, {255,140,0, 255}, "Tower 2", font);
    deleteBt = new Gomb({(behuzasi_tavolsag - 10), (emberKezdoY - 70), 40, 20},{255,165,0, 255}, {255,140,0, 255}, "Delete", font);

    kocka.h = kocka.w = 20;



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
                fomanu = false;
                singlePlayerBT->setIsVisible(false);
            }
                if (easyBt->getIsVisible() && isMouseOver(easyBt, x, y)) {
                    SDL_Log("meg van nyomva: easyBT");
                    dificulty = 1;
                    start = true;
                    easyBt->setIsVisible(false);
                    mediumBt->setIsVisible(false);
                    hardBt->setIsVisible(false);
                }else  if (mediumBt->getIsVisible() && isMouseOver(mediumBt, x, y)) {
                    SDL_Log("meg van nyomva: mediumBT");
                    dificulty = 2;
                    start = true;
                    easyBt->setIsVisible(false);
                    mediumBt->setIsVisible(false);
                    hardBt->setIsVisible(false);
                }else if (hardBt->getIsVisible() && isMouseOver(hardBt, x, y)) {
                    SDL_Log("meg van nyomva: hardBT");
                    dificulty = 3;
                    start = true;
                    easyBt->setIsVisible(false);
                    mediumBt->setIsVisible(false);
                    hardBt->setIsVisible(false);
                }else if (fighterBt->getIsVisible() && isMouseOver(fighterBt, x, y)) {
                    Fighter fighter = Fighter(0, 12 ,2, false);
                    if (money >= fighter.getPrice()) {
                        money -= fighter.getPrice();
                        CreateManToPool(fighter, false);
                    }
                }else if (rangedBt->getIsVisible() && isMouseOver(rangedBt, x, y)) {
                    Ranged ranged = Ranged(1, 8, 2, false);
                    if (money >= ranged.getPrice()) {
                        money -= ranged.getPrice();
                        CreateManToPool(ranged, false);
                    }
                }else if (tankBt->getIsVisible() && isMouseOver(tankBt, x, y)) {
                    Tank tank = Tank(2, 16, 2, false);
                    if (money >= tank.getPrice()) {
                        money -= tank.getPrice();
                        CreateManToPool(tank, false);
                    }
                }else if (mainMenuBt->getIsVisible() && isMouseOver(mainMenuBt, x, y)) {
                    fomanu = true;
                    start = false;
                    vegeMenu = false;
                    singlePlayer = false;
                    mainMenuBt->setIsVisible(false);
                }else if (tower1Bt->getIsVisible() && isMouseOver(tower1Bt, x, y)) {
                    if (money >= tower1Cost) {
                        money -= tower1Cost;
                        SDL_FRect fr;
                        if (pos == 0) {
                            fr = tower1Holder->getRect();
                            haveTower1 = true;
                            tower1Holder->setIsVisible(false);
                        }else {
                            fr = tower2Holder->getRect();
                            haveTower2 = true;
                            tower2Holder->setIsVisible(false);
                        }
                        CreateNewTower(1, 3, 10, type, fr,{238,130,238, 255}, {186,85,211, 255}, pos);
                        buyTower = false;
                    }
                    buyTower = false;
                }else if (tower2Bt->getIsVisible() && isMouseOver(tower2Bt, x, y)) {
                    if (money >= tower1Cost) {
                        money -= tower1Cost;
                        SDL_FRect fr;
                        if (type == 1) {
                            fr = tower1Holder->getRect();
                            haveTower1 = true;
                            tower1Holder->setIsVisible(false);
                        }else {
                            fr = tower2Holder->getRect();
                            haveTower2 = true;
                            tower2Holder->setIsVisible(false);
                        }
                        CreateNewTower(1, 3, 10, type, fr,{255,255,0, 255}, {204,204,0, 255}, pos);
                        buyTower = false;
                    }
                    buyTower = false;
                }else if (deleteBt->getIsVisible() && isMouseOver(deleteBt, x, y)) {
                    money += towers[deleteTowerNumber].getCost()/2;
                    towerNumber--;
                    towers[deleteTowerNumber] = Tower();
                    if (deleteTowerNumber == 0) {
                        haveTower1 = false;
                    }else {
                        haveTower2 = false;
                    }
                    deleteBt->setIsVisible(false);
                }
                else {
                    buyTower = false; // valahogz megcsinalni hogy ne mindig ugyan ugy jelenjen meg a towervasarlas
                    tower1Bt->setIsVisible(false);
                    tower2Bt->setIsVisible(false);
                    deleteBt->setIsVisible(false);
                }
            }
            if (event->button.button == SDL_BUTTON_RIGHT) {
                if (tower1Holder->getIsVisible() && isMouseOver(tower1Holder, x, y)) {
                    buyTower = true;
                    type = 1;
                    pos = 0;
                }else if (tower2Holder->getIsVisible() && isMouseOver(tower2Holder, x, y)) {
                    buyTower = true;
                    type = 2;
                    pos = 1;
                }else if (haveTower1 && isMouseOver(&towers[0], x, y)) {
                    deleteBt->setIsVisible(true);
                    deleteTowerNumber = 0;
                }else if (haveTower2 && isMouseOver(&towers[1], x, y)) {
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

    if (fomanu) {
        render_Button(singlePlayerBT);
    }
    if (singlePlayer && !start) {
        render_Button(easyBt);
        render_Button(mediumBt);
        render_Button(hardBt);
    }

    if (vege) {
        if (baseHp <= 0) {
            endText->setText("Vege sajnos te vesztettel!");
        }else {
            endText->setText("Vege te nyertel!");
        }

        start = false;
        singlePlayer = false;
        fighterBt->setIsVisible(false);
        rangedBt->setIsVisible(false);
        tankBt->setIsVisible(false);

        baseHp = maxBaseHp;
        enemybaseHp = maxEnemybaseHp;
        man = nullptr;
        manSize = 0;
        pool = nullptr;
        poolSize = 0;

        enemyMan = nullptr;
        enemyManSize = 0;
        enemyPool = nullptr;
        enemyPoolSize = 0;

        money = 20;
        aiMoney = 20;
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
        money += 1/30.0;
        std::string text = "Pénz: " + std::to_string(static_cast<int>(money));

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

        Move(renderer);

        if (!haveTower1) {
            render_Button(tower1Holder);
        }
        if (!haveTower2) {
            render_Button(tower2Holder);
        }

        for (int i = 0; i < 2; i++) {
            if (towers[i].getDmg() == 0) {
                continue;
            }
            if (towers[i].getIsVisible()) {
                renderTower(renderer, towers[i]);
            }
        }

        //xp kirajzolas:
        float ratio = static_cast<float>(xp) / static_cast<float>(100);
        float xpWidth = std::min((ratio * 100), static_cast<float>(100));
        SDL_FRect rect = {.x = 200, .y = 20, .w = 100, .h = 20};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        rect = {.x = 200, .y = 20, .w = xpWidth, .h = 20};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        text = std::to_string(xp) + "/100";

        xpText->setText(text);
        xpText->render();

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

    TTF_CloseFont(font);
    TTF_CloseFont(gombFont);

    free(window);
    free(renderer);
    free(man);
    free(pool);
    free(enemyMan);
    free(enemyPool);
    free(penzText);
    free(endText);
    free(xpText);
}