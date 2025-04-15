#ifndef VARIABLES_H
#define VARIABLES_H

#include <SDL3/SDL.h>
#include "../gui/gomb/Gomb.h"

extern Uint32 frameStart;
extern int frameTime;

extern Gomb *karakterinditas;
extern Gomb *singlePlayerBT;
extern Gomb *easyBt;
extern Gomb *mediumBt;
extern Gomb *hardBt;

extern SDL_FPoint *man;
extern size_t manSize;
extern SDL_FPoint *pool;
extern size_t poolSize;

extern bool add;
extern bool start;
extern bool singlePlayer;

extern SDL_FRect kocka;
extern float dificulty;

extern int map[7];

extern int tav;
extern float emberszelesseg;
extern float mezoszelesseg;
extern int mezoszam;

#endif // VARIABLES_H