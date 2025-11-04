#include "GameUnit.h"

GameUnit::GameUnit(int _tipus, int _hp, int _dmg, bool _isEnemy) : tipus(_tipus), hp(_hp + _hp * level * 0.25), maxHp(_hp + _hp * level * 0.25), dmg(_dmg + _dmg * level * 0.25), isEnemy(_isEnemy){
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
float GameUnit::getHp() { return hp; }
float GameUnit::getMaxHp() { return maxHp; }
int GameUnit::getTipus() { return tipus; }
float GameUnit::getDmg() { return dmg; }
int GameUnit::getRange() { return range; }
int GameUnit::getPos() { return poz; }
float GameUnit::getXp() { return xp; }
SDL_FRect GameUnit::getRect() { return rect; }
SDL_Color GameUnit::getColor() { return color; }
float GameUnit::getRextX() { return rect.x; }
bool GameUnit::getIsEnemy() { return isEnemy; }


void GameUnit::setPrice(float _price) { price = _price; };
void GameUnit::setHp(float _hp) { hp = _hp; }
void GameUnit::setMaxHp(float _maxHp) { maxHp = _maxHp; }
void GameUnit::setDmg(float _dmg) { dmg = _dmg; }
void GameUnit::setRange(int _range) { range = _range; }
void GameUnit::setPos(int _pos) { poz = _pos; }
void GameUnit::setXp(float _xp) { xp = _xp; }
void GameUnit::setRect(SDL_FRect _rect) { rect = _rect; }
void GameUnit::setColor(SDL_Color _color) { color = _color; }
void GameUnit::setRectX(float x) { rect.x = x; }

