#ifndef RANGED_H
#define RANGED_H
#include "../gameUnit/GameUnit.h"

class Ranged: public GameUnit{
public:
    Ranged(int _tipus, double _hp, double _dmg, bool _isEnemy);
    Ranged();
};

#endif //RANGED_H