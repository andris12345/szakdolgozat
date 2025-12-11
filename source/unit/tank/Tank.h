#ifndef TANK_H
#define TANK_H
#include "../gameUnit/GameUnit.h"

class Tank: public GameUnit{
public:
    Tank(int _tipus, double _hp, double _dmg, bool _isEnemy);
    Tank();
};

#endif //TANK_H