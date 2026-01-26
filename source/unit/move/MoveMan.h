#ifndef MOVEMAN_H
#define MOVEMAN_H

#include <SDL3/SDL.h>
#include "../../variables/Variables.h"
#include "../attack/Attack.h"
#include "../../variables/AiVariables.h"
#include "../create/CreateMan.h"
#include "../../gui/gomb/Gomb.h"
#include "../drawing/Drawing.h"

void Move(SDL_Renderer *renderer);
void mozgatas(GameUnit &man);
void levelUp();

#endif //MOVEMAN_H
