#include "MoveMan.h"
#include "../../variables/Variables.h"
#include "../create/CreateMan.h"
#include "../../gui/gomb/Gomb.h"



void Move(SDL_Renderer *renderer) {
    //mező jelölő vonalak
    for (int i = 0; i <= mezoszam; i++) {
        SDL_FRect rect = {.x = (mezoszelesseg * i) + tav , .y = 200-emberszelesseg/2, .w = 1, .h = emberszelesseg + emberszelesseg/2};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    if (karakterinditas) {
        render_Button(karakterinditas, renderer);
    }

    //poolban lévő emberek kirajzolása + kitevése a mapra
    for (int i = 0; i < poolSize; i++) {
        if (map[0] == 0) {
            map[0] = 1;
            CreateManToMap();

        }
        if (poolSize > 0) {
            kirajzolas(renderer, pool[i].x, pool[i].y);
        }
    }

    //kirajzolás + léptetés az embereknek
    if (manSize > 0) {
        for (int i = manSize - 1; i >= 0; i--) {
            mozgatas(man[i]);

            //kirajzolás
            kirajzolas(renderer, man[i].x, man[i].y);

            if (man[i].x >= mezoszam * mezoszelesseg + tav) {
                removeFirstManFromMap();
                map[mezoszam] = 0;
            }
        }
    }
}

void kirajzolas(SDL_Renderer *renderer, float x, float y) {
    SDL_FRect rect = {.x = x, .y = y, .w = emberszelesseg, .h = emberszelesseg};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void mozgatas(SDL_FPoint &man) {
    if (man.x < tav) {
        man.x++;
    }else {
        int hely = (man.x - tav + (emberszelesseg/2)) / mezoszelesseg;

        if (hely == mezoszam -1) {
            // man[i].x++;
        }else if (map[hely + 1] == 0 || (man.x - tav) < (hely * mezoszelesseg + 5)) {
            man.x++;
        }
        if (man.x + (emberszelesseg/2) == ((hely + 1) * mezoszelesseg) + tav) {
            map[hely] = 0;
            map[hely + 1] = 1;
        }

        if (man.x == (hely * mezoszelesseg) + tav) {
            SDL_Log(("ebben a pozban van:" + std::to_string(hely)).c_str());
        }
    }
}
