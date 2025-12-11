#include "Ranged.h"

Ranged::Ranged(int _tipus, double _hp, double _dmg, bool _isEnemy) : GameUnit(_tipus, _hp, _dmg, _isEnemy) {
    this->setColor({ 255, 0, 0, 255 });
    this->setRange(3);
}

Ranged::Ranged() {
    setRange(3);
}