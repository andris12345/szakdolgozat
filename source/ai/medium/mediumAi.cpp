#include "mediumAi.h"

void mediumAi() {
    aiMoney += 1.0 / 30;
    aiTurnCounter++;

    int playerFighters, playerRanged, playerTanks;
    analyzePlayerUnits(playerFighters, playerRanged, playerTanks);

    if (playerTanks > playerFighters + playerRanged) {
        aiStrategy = 1; // Ranged focus
    }
    else if (playerRanged > playerFighters) {
        aiStrategy = 0; // Fighter focus
    }
    else {
        aiStrategy = 2; // Mixed
    }

    if (aiTurnCounter % 600 == 0) { // ~10 másodpercenként
        if (!player2.getTowerAt(0)->isExists() && aiMoney >= tower1Cost) {
            CreateNewTower(1, 0, true);
            aiMoney -= tower1Cost;
        }
    }

    switch (aiStrategy) {
        case 0: // Fighter focus
            spawnFighterFocused();
        break;
        case 1: // Ranged focus
            spawnRangedFocused();
        break;
        case 2: // Mixed
            spawnMixed();
        break;
    }
}
