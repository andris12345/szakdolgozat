#include "Tank.h"

Tank::Tank(int _tipus, int _hp, int _dmg) : GameUnit(_tipus, _hp, _dmg) {
   this->setColor({ 0, 0, 255, 255 });
   this->setPrice(20);
   this->setRange(1);
}

Tank::Tank() {
   setRange(1);
}