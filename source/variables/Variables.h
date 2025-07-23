#ifndef VARIABLES_H
#define VARIABLES_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "../gui/felirat/Felirat.h"
#include "../unit/gameUnit/GameUnit.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;

class Gomb;
class Subtitle;

extern int width;
extern int height;

extern Uint32 frameStart;
extern Uint64 frameTime;
extern int TARGET_FPS;

extern GameUnit *man;
extern size_t manSize;
extern GameUnit *pool;
extern size_t poolSize;

extern GameUnit *enemyMan;
extern size_t enemyManSize;
extern GameUnit *enemyPool;
extern size_t enemyPoolSize;

extern bool add;
extern bool start;
extern bool singlePlayer;

extern SDL_FRect kocka;

extern float behuzasi_tavolsag;
extern float emberszelesseg;
extern float mezoszelesseg;
extern float emberKezdoY;
extern float emberKezdoX;
extern const int mezoszam;

extern int map[];

extern SDL_Color fontColor;
extern float fontSize;
extern TTF_Font *font;
extern TTF_Font *gombFont;

extern float money;
extern Subtitle *penzText;

extern Gomb *fighterBt;
extern Gomb *rangedBt;
extern Gomb *tankBt;
extern Gomb *singlePlayerBT;
extern Gomb *easyBt;
extern Gomb *mediumBt;
extern Gomb *hardBt;

extern int frameSzamlalo;

extern Gomb *startenemy;
extern GameUnit* enemy;

#include "../gui/gomb/Gomb.h"
#endif // VARIABLES_H