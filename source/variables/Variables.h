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
class Tower;
class TowerAttack;

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
extern Subtitle *endText;
extern Subtitle *xpText;

extern Gomb *fighterBt;
extern Gomb *rangedBt;
extern Gomb *tankBt;
extern Gomb *singlePlayerBT;
extern Gomb *easyBt;
extern Gomb *mediumBt;
extern Gomb *hardBt;
extern Gomb *mainMenuBt;
extern Gomb *tower1Holder;
extern Gomb *tower2Holder;
extern Gomb *tower1Bt;
extern Gomb *tower2Bt;
extern Gomb *deleteBt;

extern int deleteTowerNumber;

extern int frameSzamlalo;

extern GameUnit* enemy;

extern int maxBaseHp;
extern int baseHp;
extern int maxEnemybaseHp;
extern int enemybaseHp;
extern int xp;
extern int enemyXp;

extern bool vege;
extern bool fomanu;
extern bool vegeMenu;
extern bool buyTower;
extern bool haveTower1;
extern bool haveTower2;

extern float tower1Cost;
extern float tower2Cost;

extern int type;
extern int pos;
extern int towerNumber;
extern Tower towers[2];

extern TowerAttack& tower_attack;

#include "../gui/gomb/Gomb.h"
#include "../tower/TowerAttack.h"
#endif // VARIABLES_H