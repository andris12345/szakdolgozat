#ifndef CREATEMAN_H
#define CREATEMAN_H

#include <SDL3/SDL.h>
#include "../../variables/Variables.h"

void CreateManToMap();

void removeFirstManFromMap();

void CreateManToPool(GameUnit unit);

void removeFirstManFromPool();
#endif //CREATEMAN_H
