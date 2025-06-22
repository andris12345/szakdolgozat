#include "Fighter.h"

Fighter::Fighter(int _tipus, int _hp, int _dmg): GameUnit(_tipus, _hp, _dmg) {
   this->setColor(  { 0, 255, 0, 255 });
   this->setPrice(10);
   this->setRange(1);
}

Fighter::Fighter() {
   setRange(1);
}
