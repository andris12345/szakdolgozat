//
// Created by Andris on 2025. 07. 23..
//

#include "hardAi.h"

void hardAi() {
    aiMoney += 1.5 / 30;
    aiTurnCounter++;

    int playerFighters, playerRanged, playerTanks;
    analyzePlayerUnits(playerFighters, playerRanged, playerTanks);

    // Ellenstratégia választás
    if (player1.getManSize() > player2.getManSize() + 3) {
        // Játékos előnyben - védekezzünk tankokkal
        spawnDefensive();
    }
    else if (player1.getBaseHp() < 30) {
        // Játékos gyenge - all-in támadás
        spawnAggressive();
    }
    else {
        // Counter composition
        spawnCounter(playerFighters, playerRanged, playerTanks);
    }

}
