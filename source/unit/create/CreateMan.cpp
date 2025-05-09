#include "CreateMan.h"
#include <string>

void removeFirstManFromPool();

void CreateManToMap() {
    SDL_Log("ember generalas");
    SDL_FPoint point = pool[0];
    removeFirstManFromPool();
    manSize++;

    SDL_FPoint* temp = (SDL_FPoint*)realloc(man, manSize * sizeof(SDL_FPoint));
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

    man = (SDL_FPoint*)realloc(man, manSize * sizeof(SDL_FPoint));

    if (manSize == 0) {
        man = NULL;
    }
}

void CreateManToPool(SDL_FPoint point) {
    // N�velj�k a t�mb m�ret�t dinamikusan
    poolSize++;

    pool = (SDL_FPoint*)realloc(pool, poolSize * sizeof(SDL_FPoint));

    // �j ember besz�r�sa a t�mb v�g�re
    pool[poolSize - 1] = point;
    SDL_Log("uj pool letrehozva");
    SDL_Log(std::to_string(pool[0].x).c_str());
    SDL_Log(std::to_string(pool[0].y).c_str());
}

void removeFirstManFromPool() {
    SDL_Log("pool torles");
    if (poolSize == 0) return; // Ha nincs mit t�r�lni, kil�p�nk

    // Ha t�bb elem van, akkor el?retoljuk az elemeket
    for (size_t i = 1; i < poolSize; i++) {
        pool[i - 1] = pool[i];
    }

    poolSize--;

    pool = (SDL_FPoint*)realloc(pool, poolSize * sizeof(SDL_FPoint));

    if (poolSize == 0) {
        pool = NULL; // Ha m�r nincs ember, null�zzuk ki a pointert
    }
}