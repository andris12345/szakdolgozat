#ifndef MOVEMAN_H
#define MOVEMAN_H

#include <SDL3/SDL.h>
#include "../../variables/Variables.h"

void Move(SDL_Renderer *renderer);
void kirajzolas(SDL_Renderer *renderer, GameUnit &man);
void mozgatas(GameUnit &man);
void attackHandler(GameUnit unit_man, int hely);
void attack(GameUnit unit_man);

#endif //MOVEMAN_H
