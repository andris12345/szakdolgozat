#include "MoveMan.h"
#include "../../variables/Variables.h"
#include "../create/CreateMan.h"
#include "../../gui/gomb/Gomb.h"

void mozgatas(GameUnit &man);

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
        render_Button(rangedBt);
    }
    if (tankBt) {
        render_Button(tankBt);
    }
    if (startenemy) {
        render_Button(startenemy);
    }

    //poolban lévő emberek kirajzolása + kitevése a mapra
    for (int i = 0; i < poolSize; i++) {
        if (map[0] == 0) {
            map[0] = 1;
            CreateManToMap(false);
            SDL_Log("Created map");
        }
        if (poolSize > 0) {
            kirajzolas(renderer, pool[i]);
        }
    }

    //enemy pool kirajzolasa
    for (int i = 0; i < enemyPoolSize; i++) {

        if (map[mezoszam - 1] == 0) {
            map[mezoszam - 1] = 1;
            CreateManToMap(true);
        }
        if (enemyPoolSize > 0) {
            kirajzolas(renderer, enemyPool[i]);
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
}

void kirajzolas(SDL_Renderer *renderer, GameUnit &man) {
    SDL_FRect rect = {.x = man.getRect().x, .y = man.getRect().y, .w = emberszelesseg, .h = emberszelesseg};
    SDL_SetRenderDrawColor(renderer, man.getColor().r, man.getColor().g, man.getColor().b, 255);
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
                map[hely - 1] = 1;
            }
            if (hely + 1 == 9) {
                if (frameSzamlalo % 15 == 0)
                    tamadas();
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
            }
            if (hely + 1 == 9) {
                if (frameSzamlalo % 15 == 0)
                    tamadas();
            }
        }
    }
}

void tamadas() {
}