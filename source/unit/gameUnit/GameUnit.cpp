#include "GameUnit.h"

#include "../../variables/Variables.h"

GameUnit::GameUnit(int _tipus) : tipus(_tipus){
    this->rect = {emberKezdoX, emberKezdoY};
}

GameUnit::GameUnit(int _hp, int _dmg) : hp(_hp), dmg(_dmg) {
    this->rect = {emberKezdoX, emberKezdoY};
}

int GameUnit::getHp() { return hp; }
int GameUnit::getTipus() { return tipus; }
int GameUnit::getDmg() { return dmg; }
int GameUnit::getRange() { return range; }
SDL_FRect GameUnit::getRect() { return rect; }
SDL_Color GameUnit::getColor() { return color; }
float GameUnit::getRextX() { return rect.x; }

void GameUnit::setHp(int _hp) { hp = _hp; }
void GameUnit::setDmg(int _dmg) { dmg = _dmg; }
void GameUnit::setRange(int _range) { range = _range; }
void GameUnit::setRect(SDL_FRect _rect) { rect = _rect; }
void GameUnit::setColor(SDL_Color _color) { color = _color; }
void GameUnit::setRectX(float x) { rect.x = x; }

