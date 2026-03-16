//
// Created by Andris on 2026. 03. 16..
//

#ifndef AIUTILS_H
#define AIUTILS_H

#include "../../variables/AiVariables.h"
#include "../../unit/create/CreateMan.h"
#include "../../unit/fighter/Fighter.h"
#include "../../unit/ranged/Ranged.h"
#include "../../unit/tank/Tank.h"

// Közös helper függvények
void analyzePlayerUnits(int& fighterCount, int& rangedCount, int& tankCount);
void spawnFighterFocused();
void spawnRangedFocused();
void spawnDefensive();
void spawnAggressive();
void spawnCounter(int playerFighters, int playerRanged, int playerTanks);
void manageTowers();
void spawnMixed();

#endif //AIUTILS_H
