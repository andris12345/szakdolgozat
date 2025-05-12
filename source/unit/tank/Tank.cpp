#include "Tank.h"

Tank::Tank() = default;

Tank::Tank(int _hp, int _dmg) {
    this->hp = _hp;
    this->dmg = _dmg;
    this->range = 1;
}

int Tank::getHp() {
    return this->hp;
}

int Tank::getDmg() {
    return this->dmg;
}

int Tank::getRange() {
    return this->range;
}

void Tank::setHp(int _hp) {
    this->hp = _hp;
}

void Tank::setDmg(int _dmg) {
    this->dmg = _dmg;
}

void Tank::setRange(int _range) {
    this->range = _range;
}