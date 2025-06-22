#ifndef TANK_H
#define TANK_H
#include "../gameUnit/GameUnit.h"

class Tank: public GameUnit{
public:
    Tank(int _tipus, int _hp, int _dmg);
    Tank();
};

#endif //TANK_H