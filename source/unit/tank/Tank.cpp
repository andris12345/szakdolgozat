#include "Tank.h"

Tank::Tank(int _tipus) : GameUnit(_tipus) {
   this->setColor({ 0, 0, 255, 255 });
}

Tank::Tank(int _hp, int _dmg): GameUnit(_hp, _dmg) {
   setRange(1);
}