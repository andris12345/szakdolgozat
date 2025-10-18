#include "TowerAttack.h"

TowerAttack& TowerAttack::GetInstance() {
    static TowerAttack instance;
    return instance;
}

void TowerAttack::TowerAttackHandler() {
    for (int i = 0; i < 2; i++) {
        if (towers[i].getDmg() != 0) {
            for (int j = 0; j < towers[i].getRange(); j++) {
                if (map[j] == 2) {
                    Attack(towers[i]);
                    return;
                }
            }
        }
    }
}


void TowerAttack::Attack(Tower t) {
    GameUnit& enemy = enemyMan[0];
    enemy.setHp(enemy.getHp() - t.getDmg());
    if (enemy.getHp() <= 0) {
        map[enemy.getPos()] = 0;
        money += enemy.getPrice() / 2;
        removeFirstManFromMap(true);
    }
}

