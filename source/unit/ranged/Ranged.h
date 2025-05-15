#ifndef RANGED_H
#define RANGED_H
#include "../gameUnit/GameUnit.h"

class Ranged: public GameUnit{
public:
    Ranged(int _tipus);
    Ranged(int _hp, int _dmg);
};

#endif //RANGED_H