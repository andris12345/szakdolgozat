#include "Ranged.h"

Ranged::Ranged(int _tipus) : GameUnit(_tipus) {
    this->setColor({ 255, 0, 0, 255 });
}

Ranged::Ranged(int _hp, int _dmg): GameUnit(_hp, _dmg) {
    setRange(3);
}