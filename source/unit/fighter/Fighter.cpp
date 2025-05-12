#include "Fighter.h"

Fighter::Fighter() = default;

Fighter::Fighter(int _hp, int _dmg): GameUnit(_hp, _dmg) {
   setRange(1);
}