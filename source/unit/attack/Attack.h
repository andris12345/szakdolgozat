#ifndef ATTACK_H
#define ATTACK_H

#include <SDL3/SDL.h>
#include "../gameUnit/GameUnit.h"
#include "../../variables/Variables.h"
#include "../../variables/AiVariables.h"
#include "../create/CreateMan.h"

void attackHandler(GameUnit unit_man, int hely);
void attack(GameUnit unit_man, bool attackBase);
void attackFromPool(GameUnit unit_man, bool enemyBase);


#endif //ATTACK_H
