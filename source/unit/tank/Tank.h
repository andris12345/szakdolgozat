#ifndef TANK_H
#define TANK_H
#include "../gameUnit/GameUnit.h"

class Tank: public GameUnit{
public:
    Tank(int _tipus);
    Tank(int _hp, int _dmg);
};

#endif //TANK_H