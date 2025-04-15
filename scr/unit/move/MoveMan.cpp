#include "MoveMan.h"
#include "../../variables/Variables.h"
#include "../create/CreateMan.h"
#include "../../gui/gomb/Gomb.h"



void Move(SDL_Renderer *renderer) {
    //mező jelölő vonalak
    for (int i = 0; i <= mezoszam; i++) {
        SDL_FRect rect = {.x = (mezoszelesseg * i) + tav , .y = 200, .w = 1, .h = emberszelesseg + emberszelesseg/2};
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
            SDL_FRect rect = {.x = pool[i].x, .y = pool[i].y, .w = emberszelesseg, .h = emberszelesseg};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    //kirajzolás + léptetés az embereknek
    if (manSize > 0) {
        for (int i = manSize - 1; i >= 0; i--) {
            if (man[i].x < tav) {
                man[i].x++;
            }else {
                int hely = (man[i].x - tav + (emberszelesseg/2)) / mezoszelesseg;

                if (hely == mezoszam -1) {
                    // man[i].x++;
                }else if (map[hely + 1] == 0 || (man[i].x - tav) < (hely * mezoszelesseg + 5)) {
                    man[i].x++;
                }
                if (man[i].x + (emberszelesseg/2) == ((hely + 1) * mezoszelesseg) + tav) {
                    map[hely] = 0;
                    map[hely + 1] = 1;
                }

                if (man[i].x == (hely * mezoszelesseg) + tav) {
                    SDL_Log(("ebben a pozban van:" + std::to_string(hely)).c_str());
                }
            }

            //kirajzolás
            SDL_FRect rect = {.x = man[i].x, .y = man[i].y, .w = emberszelesseg, .h = emberszelesseg};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);

            if (man[i].x >= mezoszam * mezoszelesseg + tav) {
                removeFirstManFromMap();
                map[mezoszam] = 0;
            }
        }
    }
}