#include "easyAi.h"

void easyAi() {
    aiMoney += 0.8 / 30;
    switch (unitCounter) {
        case 0: {
            Fighter fighter = Fighter(0, 12 ,2, true);
            if (aiMoney >= fighter.getPrice()) {
                aiMoney -= fighter.getPrice();
                CreateManToPool(fighter, true);
                unitCounter++;
            }
            break;
        }
        case 1: {
            Fighter fighter = Fighter(0, 12 ,2, true);
            if (aiMoney >= fighter.getPrice()) {
                aiMoney -= fighter.getPrice();
                CreateManToPool(fighter, true);
                unitCounter++;
            }
        }
        case 2: {
            Ranged ranged = Ranged(1, 8, 2, true);
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