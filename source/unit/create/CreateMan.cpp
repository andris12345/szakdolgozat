#include "CreateMan.h"
#include <string>

void removeFirstManFromPool();

void CreateManToMap() {
    SDL_Log("ember generalas");
    GameUnit point = pool[0];
    removeFirstManFromPool();
    manSize++;

    GameUnit* temp = (GameUnit*)realloc(man, manSize * sizeof(GameUnit));
    if (temp) {
        man = temp;
        man[manSize - 1] = point;
    } else {
        SDL_Log("realloc failed in CreateManToMap");
    }
}

void removeFirstManFromMap() {
    SDL_Log("map torles");
    if (manSize == 0) return;

    for (size_t i = 1; i < manSize; i++) {
        man[i - 1] = man[i];
    }

    manSize--;

    man = (GameUnit*)realloc(man, manSize * sizeof(GameUnit));

    if (manSize == 0) {
        man = NULL;
    }
}

void CreateManToPool(GameUnit unit) {
    poolSize++;

    pool = (GameUnit*)realloc(pool, poolSize * sizeof(GameUnit));

    // uj ember beszurasa a tomb vegere
    pool[poolSize - 1] = unit;
    SDL_Log("uj pool letrehozva");
    SDL_Log(std::to_string(pool[0].getRect().x).c_str());
    SDL_Log(std::to_string(pool[0].getRect().y).c_str());
}

void removeFirstManFromPool() {
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