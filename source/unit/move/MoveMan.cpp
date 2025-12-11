#include "MoveMan.h"

#include <format>

void Move(SDL_Renderer *renderer) {
    //mező jelölő vonalak
    for (int i = 0; i <= mezoszam; i++) {
        SDL_FRect rect = {.x = (mezoszelesseg * i) + behuzasi_tavolsag , .y = 200-emberszelesseg/2, .w = 1, .h = emberszelesseg + emberszelesseg/2};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    if (fighterBt) {
        render_Button(fighterBt);
    }
    if (rangedBt) {
        render_Button(rangedBt); // todo atvinni a mainbe a buttonrendereket
    }
    if (tankBt) {
        render_Button(tankBt);
    }

    basekirajzolas(renderer);

    //poolban lévő emberek kirajzolása + kitevése a mapra
    if (!player1.getPoolIsEmpty()) {
        if (map[0] == 0) {
            player1.getPoolAt(0)->setRectX(player1.getPoolAt(0)->getRextX() + 1);
            if (player1.getPoolAt(0)->getRextX() + emberszelesseg/2 >= behuzasi_tavolsag) {
                map[0] = 1;
                CreateManToMap(false);
            }
        }
        for (int i = 0; i < player1.getPoolSize(); i++) {
            if (!player1.getPoolIsEmpty() && map[0] == 2 && (player1.getPoolAt(i)->getRange() == 3 || i == 0)) {
                if (frameSzamlalo == 0) {
                    attackFromPool(*player1.getPoolAt(i), false);
                }
            }
            if (player1.getPoolSize() > 0) {
                kirajzolas(renderer, *player1.getPoolAt(i));
            }
        }
    }

    //enemy pool kirajzolasa
    if (!player2.getPoolIsEmpty()) {
        if (map[mezoszam - 1] == 0) {
            player2.getPoolAt(0)->setRectX(player2.getPoolAt(0)->getRextX() - 1);
            if (player2.getPoolAt(0)->getRextX() + emberszelesseg/2 <= behuzasi_tavolsag + mezoszam * mezoszelesseg) {
                map[mezoszam - 1] = 2;
                CreateManToMap(true);
            }
        }
        for (int i = 0; i < player2.getPoolSize(); i++) {
            if (!player2.getPoolIsEmpty() && map[mezoszam - 1] == 1 && (player2.getPoolAt(i)->getRange() == 3 || i == 0)) {
                if (frameSzamlalo == 0) {
                    attackFromPool(*player2.getPoolAt(i), true);
                }
            }
            if (player2.getPoolSize() > 0) {
                kirajzolas(renderer, *player2.getPoolAt(i));
            }
        }
    }
    //kirajzolás + léptetés az embereknek
    if (player1.getManSize() > 0) {
        for (int i = player1.getManSize() - 1; i >= 0; i--) {
            mozgatas(*player1.getManAt(i));
            kirajzolas(renderer, *player1.getManAt(i));
        }
    }

    //enemy kirajzolasa + leptetese
    if (player2.getManSize() > 0) {
        for (int i = 0; i < player2.getManSize(); i++) {
            mozgatas(*player2.getManAt(i));
            kirajzolas(renderer, *player2.getManAt(i));
        }
    }

    //hp kirajzplas
    if (player1.getManSize() != 0) {
        if (player1.getManAt(0)->getHp() != player1.getManAt(0)->getMaxHp()) {
            hpkirajzolas(renderer, *player1.getManAt(0));
        }
    }else if (player1.getPoolSize() != 0) {
        if (player1.getPoolAt(0)->getHp() != player1.getPoolAt(0)->getMaxHp()) {
            hpkirajzolas(renderer, *player1.getPoolAt(0));
        }
    }
    if (player2.getManSize() != 0 ) {
        if (player2.getManAt(0)->getHp() != player2.getManAt(0)->getMaxHp()) {
            hpkirajzolas(renderer, *player2.getManAt(0));
        }
    }else if (player2.getPoolSize() != 0) {
        if (player2.getPoolAt(0)->getHp() != player2.getPoolAt(0)->getMaxHp()) {
            hpkirajzolas(renderer, *player2.getPoolAt(0));
        }
    }
}

void hpkirajzolas(SDL_Renderer *renderer, GameUnit &man) { //TODO: kirajzolasokat atvinni egz masik .cppbe
    float ratio = static_cast<float>(man.getHp()) / static_cast<float>(man.getMaxHp());
    float hpwidth = ratio * emberszelesseg;
    SDL_FRect rect = {.x = man.getRect().x, .y = (man.getRect().y - 15), .w = emberszelesseg, .h = 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = man.getRect().x, .y = (man.getRect().y - 15), .w = hpwidth, .h = 5};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void kirajzolas(SDL_Renderer *renderer, GameUnit &man) {
    SDL_FRect rect = {.x = man.getRect().x, .y = man.getRect().y, .w = emberszelesseg, .h = emberszelesseg};
    SDL_SetRenderDrawColor(renderer, man.getColor().r, man.getColor().g, man.getColor().b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void basekirajzolas(SDL_Renderer *renderer) {
    SDL_FRect rect = {.x = 20, .y = (emberKezdoY - 100), .w = behuzasi_tavolsag - 40, .h = emberKezdoY - 100 + emberszelesseg};
    SDL_SetRenderDrawColor(renderer, 137, 81, 41, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = (behuzasi_tavolsag + mezoszam * mezoszelesseg + 20), .y = (emberKezdoY - 100), .w = behuzasi_tavolsag - 40, .h = emberKezdoY - 100 + emberszelesseg};
    SDL_RenderFillRect(renderer, &rect);

    float ratio = static_cast<float>(player1.getBaseHp()) / static_cast<float>(maxBaseHp); // sajat
    float hpwidth = ratio * (behuzasi_tavolsag - 40);
    rect = {.x = 20, .y = (emberKezdoY - 100 - 15), .w = behuzasi_tavolsag - 40, .h = 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = 20, .y = (emberKezdoY - 100 - 15), .w = hpwidth, .h = 5};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    ratio = static_cast<float>(player2.getBaseHp()) / static_cast<float>(maxEnemybaseHp);  //enemy
    hpwidth = ratio * (behuzasi_tavolsag - 40);
    rect = {.x = behuzasi_tavolsag + mezoszam * mezoszelesseg + 20, .y = (emberKezdoY - 100 - 15), .w = behuzasi_tavolsag - 40, .h = 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = behuzasi_tavolsag + mezoszam * mezoszelesseg + 20, .y = (emberKezdoY - 100 - 15), .w = hpwidth, .h = 5};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void mozgatas(GameUnit &man){
    if (man.getIsEnemy()) {
        if ((man.getRect().x + emberszelesseg / 2) > (mezoszam - 1) * mezoszelesseg + behuzasi_tavolsag + mezoszelesseg / 2) {
            man.setRectX(man.getRextX() - 1);
        }else {
            int hely = ((man.getRextX() + emberszelesseg/2) - behuzasi_tavolsag) / mezoszelesseg;

            if (hely == 0) {
                if ((man.getRect().x + emberszelesseg / 2) > behuzasi_tavolsag + mezoszelesseg / 2) {
                    man.setRectX(man.getRextX() - 1);
                }
            }else if (map[hely - 1] == 0 || man.getRextX() > (hely * mezoszelesseg + behuzasi_tavolsag + (mezoszelesseg - emberszelesseg) / 2)) {
                man.setRectX(man.getRextX() - 1);
            }
            if (man.getRextX() + (emberszelesseg/2) == ((hely) * mezoszelesseg) + behuzasi_tavolsag - 1) {
                map[hely] = 0;
                map[hely - 1] = 2;
                man.setPos(hely - 1);
            }
            if (frameSzamlalo == 0) {
                attackHandler(man, hely);
                tower_attack.TowerAttackHandler();
            }
        }
    }else {
        if ((man.getRect().x + emberszelesseg / 2) < behuzasi_tavolsag) {
            man.setRectX(man.getRextX() + 1);
        }else {
            int hely = ((man.getRextX() + emberszelesseg/2) - behuzasi_tavolsag) / mezoszelesseg;

            if (hely == mezoszam-1) {
                if (man.getRextX() < (hely * mezoszelesseg + behuzasi_tavolsag + (mezoszelesseg - emberszelesseg) / 2)) {
                    man.setRectX(man.getRextX() + 1);
                }
            }else if (map[hely + 1] == 0 || man.getRextX() < (hely * mezoszelesseg + behuzasi_tavolsag + (mezoszelesseg - emberszelesseg) / 2)) {
                man.setRectX(man.getRextX() + 1);
            }
            if (man.getRextX() + (emberszelesseg/2) == ((hely + 1) * mezoszelesseg) + behuzasi_tavolsag) {
                map[hely] = 0;
                map[hely + 1] = 1;
                man.setPos(hely + 1);
            }
            if (frameSzamlalo == 0) {
                attackHandler(man, hely);
                tower_attack.TowerAttackHandler();
            }
        }
    }
}

void levelUp() {
    player1.setLevel(player1.getLevel() + 1);

    fighterBt->getSubtitle()->setText("Fighter: " + std::format("{:.1f}",(10 + 10 * player1.getLevel() * 0.25)));
    rangedBt->getSubtitle()->setText("Ranged: " + std::format("{:.1f}",(15 + 15 * player1.getLevel() * 0.25)));
    tankBt->getSubtitle()->setText("Tank: " +  std::format("{:.1f}",(20 + 20 * player1.getLevel() * 0.25)));


    tower1Bt->getSubtitle()->setText("Tower 1 " + std::format("{:.1f}",(10 + 10 * player1.getLevel() * 0.25)));
    tower2Bt->getSubtitle()->setText("Tower 2 " + std::format("{:.1f}",(10 + 10 * player1.getLevel() * 0.25)));
}