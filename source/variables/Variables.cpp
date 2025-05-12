#include "Variables.h"


int width = 800;
int height = 450;

Uint32 frameStart;
Uint64 frameTime;
int TARGET_FPS = 60;

Gomb *fighterBt = new Gomb({470, 0, 100, 80}, {0, 255, 0, 255}, {0, 0, 0, 255}, "Fighter");
Gomb *rangedBt = new Gomb({580, 0, 100, 80}, {0, 255, 0, 255}, {0, 0, 0, 255}, "Ranged");
Gomb *tankBt = new Gomb({690, 0, 100, 80}, {0, 255, 0, 255}, {0, 0, 0, 255}, "Tank");
Gomb *singlePlayerBT = new Gomb({350, 100, 100, 80}, {0, 255, 0, 255}, {0, 0, 0, 255},"single player");
Gomb *easyBt = new Gomb({350, 100, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255}, "easy");
Gomb *mediumBt = new Gomb({350, 200, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255}, "medium");
Gomb *hardBt = new Gomb({350, 300, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255}, "hard");
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