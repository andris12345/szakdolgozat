#ifndef VARIABLES_H
#define VARIABLES_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "../unit/gameUnit/GameUnit.h"

struct Gomb;

extern int width;
extern int height;

extern Uint32 frameStart;
extern Uint64 frameTime;
extern int TARGET_FPS;

extern Gomb *fighterBt;
extern Gomb *rangedBt;
extern Gomb *tankBt;
extern Gomb *singlePlayerBT;
extern Gomb *easyBt;
extern Gomb *mediumBt;
extern Gomb *hardBt;

extern GameUnit *man;
extern size_t manSize;
extern GameUnit *pool;
extern size_t poolSize;

extern bool add;
extern bool start;
extern bool singlePlayer;

extern SDL_FRect kocka;
extern float dificulty;

extern int map[7];

extern float behuzasi_tavolsag;
extern float emberszelesseg;
extern float mezoszelesseg;
extern float emberKezdoY;
extern float emberKezdoX;
extern int mezoszam;

extern TTF_Font *font;
extern SDL_Color fontColor;
extern float fontSize;

#include "../gui/gomb/Gomb.h"
#endif // VARIABLES_H