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

    //poolban lévő emberek kirajzolása + kitevése a mapra
    for (int i = 0; i < poolSize; i++) {
        if (map[0] == 0) {
            map[0] = 1;
            CreateManToMap();

        }
        if (poolSize > 0) {
            kirajzolas(renderer, pool[i].getRect().x, pool[i].getRect().y, pool[i].getColor());
        }
    }

    //kirajzolás + léptetés az embereknek
    if (manSize > 0) {
        for (int i = manSize - 1; i >= 0; i--) {
            mozgatas(man[i]);
            kirajzolas(renderer, man[i].getRect().x, man[i].getRect().y, man[i].getColor());

            if ((man[i].getRect().x + emberszelesseg/2) >= mezoszam * mezoszelesseg + behuzasi_tavolsag) {
                removeFirstManFromMap();
                map[mezoszam] = 0;
            }
        }
    }
}

void kirajzolas(SDL_Renderer *renderer, float x, float y, SDL_Color color) {
    SDL_FRect rect = {.x = x, .y = y, .w = emberszelesseg, .h = emberszelesseg};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void mozgatas(GameUnit &man){
    if ((man.getRect().x + emberszelesseg / 2) < behuzasi_tavolsag) {
        man.setRectX(man.getRextX() + 1);
    }else {
        int hely = ((man.getRextX() + emberszelesseg/2) - behuzasi_tavolsag) / mezoszelesseg;

        if (hely == 0) {
            //SDL_Delay(4000);
        }
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
        if ((man.getRextX() + emberszelesseg/2) == ((hely + 1) * mezoszelesseg) + behuzasi_tavolsag) {
            SDL_Log(("ebben a pozban van: " + std::to_string(hely + 1) + " ebben az xben: " + std::to_string(man.getRextX()+emberszelesseg/2)).c_str());
        }
    }
}
