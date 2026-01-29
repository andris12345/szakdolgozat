#include "Variables.h"

#include "../unit/fighter/Fighter.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int width = 800;
int height = 450;

Uint32 frameStart;
Uint64 frameTime;
int TARGET_FPS = 30;

User player1;
User player2;

bool add = false;
bool start = false;
bool singlePlayer = false;
bool multiPlayer = false;
bool client = false;
bool server = false;
bool bot = false;
SDL_FRect kocka;

float behuzasi_tavolsag = 100;
float mezoszelesseg = 40;
float emberszelesseg = 30;
float emberKezdoY = 200;
float emberKezdoX = behuzasi_tavolsag - mezoszelesseg + (mezoszelesseg/2 - emberszelesseg/2); // 100-40+(20 - 15)
const int mezoszam = 10;

int map[mezoszam] = {};

SDL_Color fontColor = {0, 0, 0};
float fontSize = 12;
TTF_Font *font;
TTF_Font *gombFont;

Subtitle *penzText = nullptr;
Subtitle *endText = nullptr;
Subtitle *xpText = nullptr;

Gomb *fighterBt = nullptr;
Gomb *rangedBt = nullptr;
Gomb *tankBt = nullptr;
Gomb *singlePlayerBT = nullptr;
Gomb *easyBt = nullptr;
Gomb *mediumBt = nullptr;
Gomb *hardBt = nullptr;
Gomb *mainMenuBt = nullptr;
Gomb *tower1Holder = nullptr;
Gomb *tower2Holder = nullptr;
Gomb *tower1Bt = nullptr;
Gomb *tower2Bt = nullptr;
Gomb *deleteBt = nullptr;
Gomb *levelUpBt = nullptr;
Gomb *multiPlayerBt = nullptr;
Gomb *exitBt = nullptr;
Gomb *hostBt = nullptr;
Gomb *joinBt = nullptr;

int deleteTowerNumber = 0;

int frameSzamlalo = 0;

int maxBaseHp = 50;                 //todo: csinalni kulon user classt es belerakni az ait is
int maxEnemybaseHp = 50;

bool vege = false;
bool fomenu = true;
bool vegeMenu = false;
bool buyTower = false;
bool haveTower1 = false;
bool haveTower2 = false;

int type = 0;
int pos = 0;
float tower1Cost = 10;
float tower2Cost = 15;


TowerAttack& tower_attack = TowerAttack::GetInstance();