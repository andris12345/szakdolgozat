#include "Fighter.h"

Fighter::Fighter(int _tipus, int _hp, int _dmg, bool _isEnemy): GameUnit(_tipus, _hp, _dmg, _isEnemy) {
   this->setColor(  { 0, 255, 0, 255 });
   this->setPrice(10 + 10 * level * 0.25);
   this->setRange(1);
   this->setXp(100 + 10 * level * 0.25);
}

Fighter::Fighter() {
   setRange(1);
}
