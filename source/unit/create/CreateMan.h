#ifndef CREATEMAN_H
#define CREATEMAN_H

#include <SDL3/SDL.h>
#include "../../variables/Variables.h"

void CreateManToMap(bool isEnemy);

void removeFirstManFromMap(bool isEnemy);

void CreateManToPool(GameUnit unit, bool isEnemy);

void removeFirstManFromPool(bool isEnemy);
#endif //CREATEMAN_H
