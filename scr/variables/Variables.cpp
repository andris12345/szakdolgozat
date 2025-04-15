#include "Variables.h"

Uint32 frameStart;
int frameTime;

Gomb *karakterinditas;
Gomb *singlePlayerBT;
Gomb *easyBt;
Gomb *mediumBt;
Gomb *hardBt;
SDL_FPoint *man;
size_t manSize;
SDL_FPoint *pool;
size_t poolSize;
bool add;
bool start;
bool singlePlayer;
SDL_FRect kocka;
float dificulty;

int map[7] = {};