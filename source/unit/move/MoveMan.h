#ifndef MOVEMAN_H
#define MOVEMAN_H

#include <SDL3/SDL.h>
#include "../../variables/Variables.h"
#include "../attack/Attack.h"
#include "../../variables/AiVariables.h"
#include "../create/CreateMan.h"
#include "../../gui/gomb/Gomb.h"

void Move(SDL_Renderer *renderer);
void hpkirajzolas(SDL_Renderer *renderer, GameUnit &man);
void kirajzolas(SDL_Renderer *renderer, GameUnit &man);
void mozgatas(GameUnit &man);
void basekirajzolas(SDL_Renderer *renderer);

#endif //MOVEMAN_H
