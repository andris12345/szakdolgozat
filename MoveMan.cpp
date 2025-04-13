#include "MoveMan.h"
#include "Variables.h"
#include "CreateMan.h"
#include "Gomb.h"

void Move(SDL_Renderer *renderer) {
    for (int i = 0; i <= 7; i++) {
        SDL_FRect rect = {.x = (float)(30 * i) , .y = 200, .w = 1, .h = 30};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    if (karakterinditas) {
        render_Button(karakterinditas, renderer);
    }

    for (int i = 0; i < poolSize; i++) {
        if (map[0] == 0) {
            map[0] = 1;
            CreateManToMap();

        }
        if (poolSize > 0) {
            SDL_FRect rect = {.x = pool[i].x, .y = pool[i].y, .w = 20, .h = 20};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    if (manSize > 0) {
        for (int i = manSize - 1; i >= 0; i--) {
            int hely = (man[i].x + 10) / 30;

            if (hely == 6) {
                // man[i].x++;
            }else if (map[hely + 1] == 0 || man[i].x < (hely * 30 + 5)) {
                man[i].x++;
            }
            if (man[i].x + 10 == (hely + 1) * 30) {
                map[hely] = 0;
                map[hely + 1] = 1;
            }

            if (man[i].x == (hely * 30)) {
                SDL_Log(("ebben a pozban van:" + std::to_string(hely)).c_str());
            }

            SDL_FRect rect = {.x = man[i].x, .y = man[i].y, .w = 20, .h = 20};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);



            if (man[i].x >= 210) {
                removeFirstManFromMap();
            }
        }
    }
}