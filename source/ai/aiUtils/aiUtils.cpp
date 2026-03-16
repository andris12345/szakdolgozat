//
// Created by Andris on 2026. 03. 16..
//

#include "aiUtils.h"

void analyzePlayerUnits(int& fighterCount, int& rangedCount, int& tankCount) {
    fighterCount = 0;
    rangedCount = 0;
    tankCount = 0;

    for (int i = 0; i < player1.getManSize(); i++) {
        GameUnit* unit = player1.getManAt(i);
        if (unit) {
            switch(unit->getTipus()) {
                case 0: fighterCount++; break;
                case 1: rangedCount++; break;
                case 2: tankCount++; break;
            }
        }
    }
    for (int i = 0; i < player1.getPoolSize(); ++i) {
        GameUnit* unit = player1.getPoolAt(i);
        if (unit) {
            switch(unit->getTipus()) {
                case 0: fighterCount++; break;
                case 1: rangedCount++; break;
                case 2: tankCount++; break;
            }
        }
    }
}

void spawnFighterFocused() {
    Fighter fighter = Fighter(0, (12 + (12 * player2.getLevel() * 0.25)),
                             (2 + (2 * player2.getLevel() * 0.25)), true);
    fighter.setPrice(10 + 10 * player2.getLevel() * 0.25);
    fighter.setXp(10 + 10 * player2.getLevel() * 0.25);

    if (aiMoney >= fighter.getPrice()) {
        aiMoney -= fighter.getPrice();
        CreateManToPool(fighter, true);
    }
}

void spawnRangedFocused() {
    Ranged ranged = Ranged(1, (8 + (8 * player2.getLevel() * 0.25)),
                          (2 + (2 * player2.getLevel() * 0.25)), true);
    ranged.setPrice(15 + 15 * player2.getLevel() * 0.25);
    ranged.setXp(10 + 10 * player2.getLevel() * 0.25);

    if (aiMoney >= ranged.getPrice()) {
        aiMoney -= ranged.getPrice();
        CreateManToPool(ranged, true);
    }
}

void spawnMixed() {
    // 2 fighter + 1 ranged minta
    switch (unitCounter % 3) {
        case 0:
        case 1:
            spawnFighterFocused();
        unitCounter++;
        break;
        case 2:
            spawnRangedFocused();
        unitCounter++;
        break;
    }
}

void manageTowers() {
    if (!player2.getTowerAt(0)->isExists() && aiMoney >= tower1Cost) {
        CreateNewTower(1, 0, true);
        aiMoney -= tower1Cost;
    }
    else if (!player2.getTowerAt(1)->isExists() && aiMoney >= tower2Cost) {
        CreateNewTower(2, 1, true);
        aiMoney -= tower2Cost;
    }
}

void spawnDefensive() {
    if (unitCounter % 2 == 0) {
        Tank tank = Tank(2, (16 + (16 * player2.getLevel() * 0.25)),
                        (2 + (2 * player2.getLevel() * 0.25)), true);
        tank.setPrice(20 + 20 * player2.getLevel() * 0.25);
        tank.setXp(20 + 20 * player2.getLevel() * 0.25);

        if (aiMoney >= tank.getPrice()) {
            aiMoney -= tank.getPrice();
            CreateManToPool(tank, true);
            unitCounter++;
        }
    } else {
        spawnRangedFocused();
        unitCounter++;
    }
}

void spawnAggressive() {
    Fighter fighter = Fighter(0, (12 + (12 * player2.getLevel() * 0.25)),
                             (2 + (2 * player2.getLevel() * 0.25)), true);
    fighter.setPrice(10 + 10 * player2.getLevel() * 0.25);
    fighter.setXp(10 + 10 * player2.getLevel() * 0.25);

    if (aiMoney >= fighter.getPrice()) {
        aiMoney -= fighter.getPrice();
        CreateManToPool(fighter, true);
    }
}

void spawnCounter(int playerFighters, int playerRanged, int playerTanks) {

    if (playerTanks >= playerFighters && playerTanks >= playerRanged) {
        // Ellenük ranged
        spawnRangedFocused();
    }
    else if (playerRanged >= playerFighters) {
        // Ellenük fighter
        spawnFighterFocused();
    }
    else {
        // Ellenük tank
        Tank tank = Tank(2, (16 + (16 * player2.getLevel() * 0.25)),
                        (2 + (2 * player2.getLevel() * 0.25)), true);
        tank.setPrice(20 + 20 * player2.getLevel() * 0.25);
        tank.setXp(20 + 20 * player2.getLevel() * 0.25);

        if (aiMoney >= tank.getPrice()) {
            aiMoney -= tank.getPrice();
            CreateManToPool(tank, true);
        }
    }
}