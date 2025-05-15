#ifndef FIGHTER_H
#define FIGHTER_H
#include "../gameUnit/GameUnit.h"

class Fighter: public GameUnit{
public:
    Fighter(int _tipus);
    Fighter(int _hp, int _dmg);
};

#endif //FIGHTER_H