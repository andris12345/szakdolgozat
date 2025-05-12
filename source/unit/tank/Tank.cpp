#include "Tank.h"

Tank::Tank() = default;

Tank::Tank(int _hp, int _dmg): GameUnit(_hp, _dmg) {
   setRange(1);
}