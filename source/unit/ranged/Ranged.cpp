﻿#include "Ranged.h"

Ranged::Ranged(int _tipus, int _hp, int _dmg, bool _isEnemy) : GameUnit(_tipus, _hp, _dmg, _isEnemy) {
    this->setColor({ 255, 0, 0, 255 });
    this->setPrice(15);
    this->setRange(3);
}

Ranged::Ranged() {
    setRange(3);
}