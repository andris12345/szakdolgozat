#include "Ranged.h"

Ranged::Ranged() = default;

Ranged::Ranged(int _hp, int _dmg) {
    this->hp = _hp;
    this->dmg = _dmg;
    this->range = 3;
}

int Ranged::getHp() {
    return this->hp;
}

int Ranged::getDmg() {
    return this->dmg;
}

int Ranged::getRange() {
    return this->range;
}

void Ranged::setHp(int _hp) {
    this->hp = _hp;
}

void Ranged::setDmg(int _dmg) {
    this->dmg = _dmg;
}

void Ranged::setRange(int _range) {
    this->range = _range;
}