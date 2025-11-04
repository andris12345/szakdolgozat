#include "Tank.h"

Tank::Tank(int _tipus, int _hp, int _dmg, bool _isEnemy) : GameUnit(_tipus, _hp, _dmg, _isEnemy) {
   this->setColor({ 0, 0, 255, 255 });
   this->setPrice(20);
   this->setRange(1);
   this->setXp(20);
}

Tank::Tank() {
   setRange(1);
}