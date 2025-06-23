#ifndef MOVEMAN_H
#define MOVEMAN_H

#include <SDL3/SDL.h>
#include "../../variables/Variables.h"

void Move(SDL_Renderer *renderer);
void kirajzolas(SDL_Renderer *renderer, GameUnit &man);
void mozgatas(GameUnit &man);
void tamadas();

#endif //MOVEMAN_H
