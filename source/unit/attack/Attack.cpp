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
            if (!player1.getPoolIsEmpty()) {
                enemy = player1.getPoolAt(0);
                enemy->setHp(enemy->getHp() - unit_man.getDmg());
                if (enemy->getHp() <= 0) {
                    aiMoney += enemy->getPrice() / 2;
                    player2.setXp(player2.getXp() + enemy->getXp());
                    removeFirstManFromPool(false);
                }
            }else {
                player1.setBaseHp(player1.getBaseHp() - unit_man.getDmg());
                if (player1.getBaseHp() <= 0) {
                    SDL_Log("vege van a mecsnek");
                    vege = true;
                }
            }
        }else {
            enemy = player1.getManAt(0);
            enemy->setHp(enemy->getHp() - unit_man.getDmg());
            if (enemy->getHp() <= 0) {
                map[enemy->getPos()] = 0;
                aiMoney += enemy->getPrice() / 2;
                player2.setXp(player2.getXp() + enemy->getXp());
                removeFirstManFromMap(false);   //todo: megcsinalni szebbre
            }
        }

    }else {                                         //en
        if (attackBase) {
            if (NULL != player2.getPool()) {
                enemy = player2.getPoolAt(0);
                enemy->setHp(enemy->getHp() - unit_man.getDmg());
                if (enemy->getHp() <= 0) {
                    player1.setMoney(player1.getMoney() + (enemy->getPrice() / 2));
                    player1.setXp(player1.getXp() + enemy->getXp());
                    removeFirstManFromPool(true);
                }
            }else {
                player2.setBaseHp(player2.getBaseHp() - unit_man.getDmg());
                if (player2.getBaseHp() <= 0) {
                    vege = true;
                }
            }
        }else {
            enemy = player2.getManAt(0);
            enemy->setHp(enemy->getHp() - unit_man.getDmg());
            if (enemy->getHp() <= 0) {
                map[enemy->getPos()] = 0;
                player1.setMoney(player1.getMoney() + (enemy->getPrice() / 2));
                player1.setXp(player1.getXp() + enemy->getXp());
                removeFirstManFromMap(true);
            }
        }
    }
}

void attackFromPool(GameUnit unit_man, bool enemyBase) {
    GameUnit* enemy = nullptr;
    if (enemyBase) {
        enemy = player1.getManAt(0);
        enemy->setHp(enemy->getHp() - unit_man.getDmg());
        if (enemy->getHp() <= 0) {
            map[mezoszam - 1] = 0;
            aiMoney += enemy->getPrice() / 2;
            player2.setXp(player2.getXp() + enemy->getXp());
            removeFirstManFromMap(false);
        }
    }else {
        enemy = player2.getManAt(0);
        enemy->setHp(enemy->getHp() - unit_man.getDmg());
        if (enemy->getHp() <= 0) {
            map[0] = 0;
            player1.setMoney(player1.getMoney() + (enemy->getPrice() / 2));
            player1.setXp(player1.getXp() + enemy->getXp());
            removeFirstManFromMap(true);
        }
    }
}
