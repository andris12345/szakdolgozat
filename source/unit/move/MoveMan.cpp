#include "MoveMan.h"
#include "../../variables/Variables.h"
#include "../../variables/AiVariables.h"
#include "../create/CreateMan.h"
#include "../../gui/gomb/Gomb.h"

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
    if (pool != NULL) {
        if (map[0] == 0) {
            pool[0].setRectX(pool[0].getRextX() + 1);
            if (pool[0].getRextX() + emberszelesseg/2 >= behuzasi_tavolsag) {
                map[0] = 1;
                CreateManToMap(false);
            }
        }
        for (int i = 0; i < poolSize; i++) {
            if (pool != NULL && map[0] == 2 && (pool[i].getRange() == 3 || i == 0)) {
                if (frameSzamlalo == 0) {
                    attackFromPool(pool[i], false);
                }
            }
            if (poolSize > 0) {
                kirajzolas(renderer, pool[i]);
            }
        }
    }

    //enemy pool kirajzolasa
    if (enemyPool != NULL) {
        if (map[mezoszam - 1] == 0) {
            enemyPool[0].setRectX(enemyPool[0].getRextX() - 1);
            if (enemyPool[0].getRextX() + emberszelesseg/2 <= behuzasi_tavolsag + mezoszam * mezoszelesseg) {
                map[mezoszam - 1] = 2;
                CreateManToMap(true);
            }
        }
        for (int i = 0; i < enemyPoolSize; i++) {
            if (enemyPool != NULL && map[mezoszam - 1] == 1 && (enemyPool[i].getRange() == 3 || i == 0)) {
                if (frameSzamlalo == 0) {
                    attackFromPool(enemyPool[i], true);
                }
            }
            if (enemyPoolSize > 0) {
                kirajzolas(renderer, enemyPool[i]);
            }
        }
    }

    //kirajzolás + léptetés az embereknek
    if (manSize > 0) {
        for (int i = manSize - 1; i >= 0; i--) {
            mozgatas(man[i]);
            kirajzolas(renderer, man[i]);
        }
    }

    //enemy kirajzolasa + leptetese
    if (enemyManSize > 0) {
        for (int i = 0; i < enemyManSize; i++) {
            mozgatas(enemyMan[i]);
            kirajzolas(renderer, enemyMan[i]);
        }
    }

    //hp kirajzplas
    if (manSize != 0) {
        if (man[0].getHp() != man[0].getMaxHp()) {
            hpkirajzolas(renderer, man[0]);
        }
    }else if (poolSize != 0) {
        if (pool[0].getHp() != pool[0].getMaxHp()) {
            hpkirajzolas(renderer, pool[0]);
        }
    }
    if (enemyManSize != 0 ) {
        if (enemyMan[0].getHp() != enemyMan[0].getMaxHp()) {
            hpkirajzolas(renderer, enemyMan[0]);
        }
    }else if (enemyPoolSize != 0) {
        if (enemyPool[0].getHp() != enemyPool[0].getMaxHp()) {
            hpkirajzolas(renderer, enemyPool[0]);
        }
    }
}

void hpkirajzolas(SDL_Renderer *renderer, GameUnit &man) {
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

    float ratio = static_cast<float>(baseHp) / static_cast<float>(maxBaseHp); // sajat
    float hpwidth = ratio * (behuzasi_tavolsag - 40);
    rect = {.x = 20, .y = (emberKezdoY - 100 - 15), .w = behuzasi_tavolsag - 40, .h = 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = 20, .y = (emberKezdoY - 100 - 15), .w = hpwidth, .h = 5};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    ratio = static_cast<float>(enemybaseHp) / static_cast<float>(maxEnemybaseHp);  //enemy
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
            }
        }
    }
}
