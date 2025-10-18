#include "Variables.h"

#include "../unit/fighter/Fighter.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int width = 800;
int height = 450;

Uint32 frameStart;
Uint64 frameTime;
int TARGET_FPS = 30;

GameUnit *man;
size_t manSize;
GameUnit *pool;
size_t poolSize;

GameUnit *enemyMan;
size_t enemyManSize;
GameUnit *enemyPool;
size_t enemyPoolSize;

bool add;
bool start;
bool singlePlayer;
SDL_FRect kocka;

float behuzasi_tavolsag = 100;
float mezoszelesseg = 40;
float emberszelesseg = 30;
float emberKezdoY = 200;
float emberKezdoX = behuzasi_tavolsag - mezoszelesseg + (mezoszelesseg/2 - emberszelesseg/2);;
const int mezoszam = 10;

int map[mezoszam] = {};

SDL_Color fontColor = {0, 0, 0};
float fontSize = 12;
TTF_Font *font;
TTF_Font *gombFont;

float money = 20;
Subtitle *penzText = nullptr;
Subtitle *endText = nullptr;

Gomb *fighterBt = nullptr;
Gomb *rangedBt = nullptr;
Gomb *tankBt = nullptr;
Gomb *singlePlayerBT = nullptr;
Gomb *easyBt = nullptr;
Gomb *mediumBt = nullptr;
Gomb *hardBt = nullptr;
Gomb *mainMenuBt = nullptr;
Gomb *tower1Bt = nullptr;
Gomb *tower2Bt = nullptr;
Gomb *towerType1Bt = nullptr;
Gomb *towerType2Bt = nullptr;

int frameSzamlalo = 0;

int maxBaseHp = 50;                 //todo: csinalni kulon user classt es belerakni az ait is
int baseHp = maxBaseHp;
int maxEnemybaseHp = 50;
int enemybaseHp = maxEnemybaseHp;

bool vege = false;
bool fomanu = true;
bool vegeMenu = false;
bool buyTower = false;
bool haveTower1 = false;
bool haveTower2 = false;

int type = 0;
int pos = 0;
float tower1Cost = 10;
float tower2Cost = 15;

int towerNumber = 0;
Tower towers[2];

TowerAttack& tower_attack = TowerAttack::GetInstance();