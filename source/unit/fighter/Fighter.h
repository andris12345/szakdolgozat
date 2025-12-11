#ifndef FIGHTER_H
#define FIGHTER_H
#include "../gameUnit/GameUnit.h"

class Fighter: public GameUnit{
public:
    Fighter(int _tipus, double _hp, double _dmg, bool _isEnemy);
    Fighter();
};

#endif //FIGHTER_H