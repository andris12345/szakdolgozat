#ifndef DRAWING_H
#define DRAWING_H


#include "../../variables/Variables.h"

void hpKirajzolasHelper();
void hpkirajzolas(SDL_Renderer *renderer, GameUnit &man);
void kirajzolas(SDL_Renderer *renderer, GameUnit &man);
void basekirajzolas(SDL_Renderer *renderer);
void unitKirajzolas(SDL_Renderer *renderer);
void toronyKirajzolas(SDL_Renderer *renderer);

#endif //DRAWING_H
