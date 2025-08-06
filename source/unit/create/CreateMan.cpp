#include "CreateMan.h"
#include <string>

void removeFirstManFromPool(bool isEnemy);

void CreateManToMap(bool isEnemy) {
    if (isEnemy) {
        SDL_Log("enemy create to map");
        GameUnit point = enemyPool[0];
        point.setPos(mezoszam - 1);
        removeFirstManFromPool(isEnemy);
        enemyManSize++;
        SDL_Log("delete enemy from pool");
        GameUnit* temp = (GameUnit*)realloc(enemyMan, enemyManSize * sizeof(GameUnit));
        if (temp) {
            enemyMan = temp;
            enemyMan[enemyManSize - 1] = point;
        } else {
            SDL_Log("realloc failed in CreateManToMap");
        }
    }else {
        SDL_Log("ember generalas");
        GameUnit point = pool[0];
        point.setPos(0);
        removeFirstManFromPool(isEnemy);
        manSize++;
        SDL_Log("delete man from pool");
        GameUnit* temp = (GameUnit*)realloc(man, manSize * sizeof(GameUnit));
        if (temp) {
            man = temp;
            man[manSize - 1] = point;
        } else {
            SDL_Log("realloc failed in CreateManToMap");
        }
    }
}

void removeFirstManFromMap(bool isEnemy) {
    if (isEnemy) {
        if (enemyManSize == 0) return;

        map[enemyMan[0].getPos()] = 0;

        for (size_t i = 1; i < enemyManSize; i++) {
            enemyMan[i - 1] = enemyMan[i];
        }

        enemyManSize--;

        enemyMan = (GameUnit*)realloc(enemyMan, enemyManSize * sizeof(GameUnit));

        if (enemyManSize == 0) {
            enemyMan = NULL;
        }
    }else {
        SDL_Log("map torles");
        if (manSize == 0) return;

        map[man[0].getPos()] = 0;

        for (size_t i = 1; i < manSize; i++) {
            man[i - 1] = man[i];
        }

        manSize--;

        man = (GameUnit*)realloc(man, manSize * sizeof(GameUnit));

        if (manSize == 0) {
            man = NULL;
        }
    }
}

void CreateManToPool(GameUnit unit, bool isEnemy) {
    if (isEnemy) {
        unit.setPos(mezoszam);
        SDL_Log("enemy");
        enemyPoolSize++;
        enemyPool = (GameUnit*)realloc(enemyPool, enemyPoolSize * sizeof(GameUnit));

        // uj ember beszurasa a tomb vegere
        enemyPool[enemyPoolSize - 1] = unit;
        SDL_Log("uj enemyPool letrehozva");
        SDL_Log(std::to_string(enemyPool[0].getRect().x).c_str());
        SDL_Log(std::to_string(enemyPool[0].getRect().y).c_str());
    }else {
        unit.setPos(0);
        poolSize++;

        pool = (GameUnit*)realloc(pool, poolSize * sizeof(GameUnit));

        // uj ember beszurasa a tomb vegere
        pool[poolSize - 1] = unit;
        SDL_Log("uj pool letrehozva");
        SDL_Log(std::to_string(pool[0].getRect().x).c_str());
        SDL_Log(std::to_string(pool[0].getRect().y).c_str());
    }
}

void removeFirstManFromPool(bool isEnemy) {
    if (isEnemy) {
        if (enemyPoolSize == 0) return; // Ha nincs mit t�r�lni, kil�p�nk

        // Ha tobb elem van, akkor eloretoljuk az elemeket
        for (size_t i = 1; i < enemyPoolSize; i++) {
            enemyPool[i - 1] = enemyPool[i];
        }

        enemyPoolSize--;

        enemyPool = (GameUnit*)realloc(enemyPool, enemyPoolSize * sizeof(GameUnit));

        if (enemyPoolSize == 0) {
            enemyPool = NULL; // Ha mar nincs ember, nullazzuk ki a pointert
        }
    }else {
        SDL_Log("pool torles");
        if (poolSize == 0) return; // Ha nincs mit t�r�lni, kil�p�nk

        // Ha tobb elem van, akkor eloretoljuk az elemeket
        for (size_t i = 1; i < poolSize; i++) {
            pool[i - 1] = pool[i];
        }

        poolSize--;

        pool = (GameUnit*)realloc(pool, poolSize * sizeof(GameUnit));

        if (poolSize == 0) {
            pool = NULL; // Ha mar nincs ember, nullazzuk ki a pointert
        }
    }
}