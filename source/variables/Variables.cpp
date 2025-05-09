#include "Variables.h"

Uint32 frameStart;
Uint64 frameTime;
int TARGET_FPS = 60;

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

float behuzasi_tavolsag = 100;
float mezoszelesseg = 40;
float emberszelesseg = 30;
int mezoszam = 7;

SDL_Color fontColor = {0, 0, 0};
float fontSize = 12;
TTF_Font *font = TTF_OpenFont("D:/CLion/szakdolgozat/assets/albert-text/AlbertText-Bold.ttf", fontSize);