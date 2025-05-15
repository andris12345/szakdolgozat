#include "Fighter.h"

Fighter::Fighter(int _tipus): GameUnit(_tipus) {
   this->setColor(  { 0, 255, 0, 255 });
}

Fighter::Fighter(int _hp, int _dmg): GameUnit(_hp, _dmg) {
   setRange(1);
}
