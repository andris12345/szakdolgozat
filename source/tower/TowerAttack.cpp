#include "TowerAttack.h"

TowerAttack& TowerAttack::GetInstance() {
    static TowerAttack instance;
    return instance;
}

void TowerAttack::TowerAttackHandler() {
    for (int i = 0; i < 2; i++) {
        if (player1.getTowerAt(i)->isExists()) {
            for (int j = 0; j < player1.getTowerAt(i)->getRange(); j++) {
                if (map[j] == 2) {
                    Attack(*player1.getTowerAt(i), true);
                    return;
                }
            }
        }
        if (player2.getTowerAt(i)->isExists()) {
            for (int j = 0; j < player2.getTowerAt(i)->getRange(); j++) {
                if (map[mezoszam-1-j] == 1) {
                    Attack(*player2.getTowerAt(i), false);
                    return;
                }
            }
        }
    }
}


void TowerAttack::Attack(Tower t, bool p1) {
    if (p1) {
        GameUnit& enemy = *player2.getManAt(0);
        enemy.setHp(enemy.getHp() - t.getDmg());
        if (enemy.getHp() <= 0) {
            map[enemy.getPos()] = 0;
            player1.setMoney(player1.getMoney() + (enemy.getPrice() / 2));
            removeFirstManFromMap(true);
        }
    }else {
        GameUnit& enemy = *player1.getManAt(0);
        enemy.setHp(enemy.getHp() - t.getDmg());
        if (enemy.getHp() <= 0) {
            map[enemy.getPos()] = 0;
            player2.setMoney(player2.getMoney() + (enemy.getPrice() / 2));
            removeFirstManFromMap(false);
        }
    }

}

