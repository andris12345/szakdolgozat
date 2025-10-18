#ifndef TOWERATTACK_H
#define TOWERATTACK_H

#include "Tower.h"
#include "../unit/create/CreateMan.h"

class TowerAttack {
private:
    TowerAttack() = default;
    ~TowerAttack() = default;

    void Attack(Tower tower);

public:
    static TowerAttack& GetInstance();
    void TowerAttackHandler();

    TowerAttack(const TowerAttack&) = delete;
    TowerAttack& operator=(const TowerAttack&) = delete;
};




#endif //TOWERATTACK_H
