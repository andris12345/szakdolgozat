#include "Attack.h"

void attackHandler(GameUnit unit_man, int hely) {
    if (unit_man.getIsEnemy()) {                    //bot
        if (hely == 0) {
            attack(unit_man, true);
        }else {
            for (int i = 1; i <= unit_man.getRange(); i++) {
                if (map[hely - i] == 1) {
                    attack(unit_man, false);
                }
            }
        }
    }else {                                         //en
        if (hely == mezoszam - 1) {
            attack(unit_man, true);
        }else {
            for (int i = 1; i <= unit_man.getRange(); i++) {
                if (map[hely + i] == 2) {
                    attack(unit_man, false);
                }
            }
        }
    }
}

void attack(GameUnit unit_man, bool attackBase) {
    GameUnit* enemy;
    if (unit_man.getIsEnemy()) {                    //bot
        if (attackBase) {
            if (NULL != pool) {
                enemy = &pool[0];
                enemy->setHp(enemy->getHp() - unit_man.getDmg());
                if (enemy->getHp() <= 0) {
                    aiMoney += enemy->getPrice() / 2;
                    removeFirstManFromPool(false);
                }
            }else {
                baseHp -= unit_man.getDmg();
            }
        }else {
            enemy = &man[0];
            enemy->setHp(enemy->getHp() - unit_man.getDmg());
            if (enemy->getHp() <= 0) {
                map[enemy->getPos()] = 0;
                aiMoney += enemy->getPrice() / 2;
                removeFirstManFromMap(false);   //todo: megcsinalni szebbre
            }
        }

    }else {                                         //en
        if (attackBase) {
            if (NULL != enemyPool) {
                enemy = &enemyPool[0];
                enemy->setHp(enemy->getHp() - unit_man.getDmg());
                if (enemy->getHp() <= 0) {
                    money += enemy->getPrice() / 2;
                    removeFirstManFromPool(true);
                }
            }else {
                enemybaseHp -= unit_man.getDmg();
            }
        }else {
            enemy = &enemyMan[0];
            enemy->setHp(enemy->getHp() - unit_man.getDmg());
            if (enemy->getHp() <= 0) {
                map[enemy->getPos()] = 0;
                money += enemy->getPrice() / 2;
                removeFirstManFromMap(true);
            }
        }
    }
}

void attackFromPool(GameUnit unit_man, bool enemyBase) {
    GameUnit* enemy = nullptr;
    if (enemyBase) {
        enemy = &man[0];
        enemy->setHp(enemy->getHp() - unit_man.getDmg());
        if (enemy->getHp() <= 0) {
            map[mezoszam - 1] = 0;
            aiMoney += enemy->getPrice() / 2;
            removeFirstManFromMap(false);
        }
    }else {
        enemy = &enemyMan[0];
        enemy->setHp(enemy->getHp() - unit_man.getDmg());
        if (enemy->getHp() <= 0) {
            map[0] = 0;
            money += enemy->getPrice() / 2;
            removeFirstManFromMap(true);
        }
    }
}
