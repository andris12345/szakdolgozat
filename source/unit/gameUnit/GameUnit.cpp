#include "GameUnit.h"

#include "../../variables/Variables.h"

GameUnit::GameUnit(int _tipus, int _hp, int _dmg, bool _isEnemy) : tipus(_tipus), hp(_hp), dmg(_dmg), isEnemy(_isEnemy){
    if (_isEnemy) {
        this->rect = {mezoszam * mezoszelesseg + behuzasi_tavolsag + mezoszelesseg/2 - emberszelesseg/2, emberKezdoY};
    }else {
        this->rect = {emberKezdoX, emberKezdoY};
    }
}

GameUnit::GameUnit() {
    this->rect = {emberKezdoX, emberKezdoY};
}

float GameUnit::getPrice() { return price; }
int GameUnit::getHp() { return hp; }
int GameUnit::getTipus() { return tipus; }
int GameUnit::getDmg() { return dmg; }
int GameUnit::getRange() { return range; }
int GameUnit::getPos() { return poz; }
SDL_FRect GameUnit::getRect() { return rect; }
SDL_Color GameUnit::getColor() { return color; }
float GameUnit::getRextX() { return rect.x; }
bool GameUnit::getIsEnemy() { return isEnemy; }


void GameUnit::setPrice(float _price) { price = _price; };
void GameUnit::setHp(int _hp) { hp = _hp; }
void GameUnit::setDmg(int _dmg) { dmg = _dmg; }
void GameUnit::setRange(int _range) { range = _range; }
void GameUnit::setPos(int _pos) { poz = _pos; }
void GameUnit::setRect(SDL_FRect _rect) { rect = _rect; }
void GameUnit::setColor(SDL_Color _color) { color = _color; }
void GameUnit::setRectX(float x) { rect.x = x; }

