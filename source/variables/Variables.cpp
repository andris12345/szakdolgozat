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
Gomb *fighterBt = nullptr;
Gomb *rangedBt = nullptr;
Gomb *tankBt = nullptr;
Gomb *singlePlayerBT = nullptr;
Gomb *easyBt = nullptr;
Gomb *mediumBt = nullptr;
Gomb *hardBt = nullptr;

int frameSzamlalo = 0;

int maxBaseHp = 50;
int baseHp = maxBaseHp;
int maxEnemybaseHp = 50;
int enemybaseHp = maxEnemybaseHp;

bool vege = false;