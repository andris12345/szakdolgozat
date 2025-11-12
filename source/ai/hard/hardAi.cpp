//
// Created by Andris on 2025. 07. 23..
//

#include "hardAi.h"

void hardAi() {
    aiMoney += 1.5 / 30;
    switch (unitCounter) {
        case 0: {
            Fighter fighter = Fighter(0, (12 + (12 * enemyLevel * 0.25)),(2 + (2 * enemyLevel * 0.25)), true);
            fighter.setPrice(10 + 10 * enemyLevel * 0.25);
            fighter.setXp(10 + 10 * enemyLevel * 0.25);
            if (aiMoney >= fighter.getPrice()) {
                aiMoney -= fighter.getPrice();
                CreateManToPool(fighter, true);
                unitCounter++;
            }
            break;
        }
        case 1: {
            Fighter fighter = Fighter(0, (12 + (12 * enemyLevel * 0.25)),(2 + (2 * enemyLevel * 0.25)), true);
            fighter.setPrice(10 + 10 * enemyLevel * 0.25);
            fighter.setXp(10 + 10 * enemyLevel * 0.25);
            if (aiMoney >= fighter.getPrice()) {
                aiMoney -= fighter.getPrice();
                CreateManToPool(fighter, true);
                unitCounter++;
            }
        }
        case 2: {
            Ranged ranged = Ranged(1, (8 + (8 * enemyLevel * 0.25)), (2 + (2 * enemyLevel * 0.25)), true);
            ranged.setPrice(15 + 15 * enemyLevel * 0.25);
            ranged.setXp(10 + 10 * enemyLevel * 0.25);
            if (aiMoney >= ranged.getPrice()) {
                aiMoney -= ranged.getPrice();
                unitCounter = 0;
                CreateManToPool(ranged, true);

            }
            break;
        }
        default:
            break;
    }
}
