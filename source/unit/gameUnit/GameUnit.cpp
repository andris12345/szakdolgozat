#include "GameUnit.h"

#include "../../variables/Variables.h"

GameUnit::GameUnit() = default;

GameUnit::GameUnit(int _hp, int _dmg) : hp(_hp), dmg(_dmg) {
    this->rect = {emberKezdoX, emberKezdoY};
}

int GameUnit::getHp() { return hp; }
int GameUnit::getDmg() { return dmg; }
int GameUnit::getRange() { return range; }

void GameUnit::setHp(int _hp) { hp = _hp; }
void GameUnit::setDmg(int _dmg) { dmg = _dmg; }
void GameUnit::setRange(int _range) { range = _range; }
