#include "Fighter.h"

Fighter::Fighter() = default;

Fighter::Fighter(int _hp, int _dmg) {
    this->hp = _hp;
    this->dmg = _dmg;
    this->range = 1;
}

int Fighter::getHp() {
    return this->hp;
}

int Fighter::getDmg() {
    return this->dmg;
}

int Fighter::getRange() {
    return this->range;
}

void Fighter::setHp(int _hp) {
    this->hp = _hp;
}

void Fighter::setDmg(int _dmg) {
    this->dmg = _dmg;
}

void Fighter::setRange(int _range) {
    this->range = _range;
}



