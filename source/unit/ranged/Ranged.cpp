#include "Ranged.h"

Ranged::Ranged() = default;

Ranged::Ranged(int _hp, int _dmg): GameUnit(_hp, _dmg) {
    setRange(3);
}