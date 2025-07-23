#ifndef MOVEMAN_H
#define MOVEMAN_H

#include <SDL3/SDL.h>
#include "../../variables/Variables.h"
#include "../attack/Attack.h"

void Move(SDL_Renderer *renderer);
void kirajzolas(SDL_Renderer *renderer, GameUnit &man);
void mozgatas(GameUnit &man);

#endif //MOVEMAN_H
