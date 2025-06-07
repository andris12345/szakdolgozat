#include "Variables.h"

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
bool add;
bool start;
bool singlePlayer;
SDL_FRect kocka;
float dificulty;

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

float penz = 10;
Subtitle *penzText = nullptr;
Gomb *fighterBt = nullptr;
Gomb *rangedBt = nullptr;
Gomb *tankBt = nullptr;
Gomb *singlePlayerBT = nullptr;
Gomb *easyBt = nullptr;
Gomb *mediumBt = nullptr;
Gomb *hardBt = nullptr;
