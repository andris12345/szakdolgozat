#include "CreateMan.h"
#include <string>

void removeFirstManFromPool(bool isEnemy);

void CreateManToMap(bool isEnemy) {
    if (isEnemy) {
        SDL_Log("enemy create to map");
        GameUnit point = *player2.getPoolAt(0);
        point.setPos(mezoszam - 1);
        removeFirstManFromPool(isEnemy);
        player2.setManSize(player2.getManSize() + 1);
        SDL_Log("delete enemy from pool");

        if (player2.reallocMan(player2.getManSize())) {
            player2.setManAt(player2.getManSize() - 1, &point);
        } else {
            SDL_Log("realloc failed in CreateManToMap player2");
        }
    }else {
        SDL_Log("ember generalas");
        GameUnit point = *player1.getPoolAt(0);
        point.setPos(0);
        removeFirstManFromPool(isEnemy);
        player1.setManSize(player1.getManSize() + 1);
        SDL_Log("delete man from pool");

        if (player1.reallocMan(player1.getManSize())) {
            player1.setManAt(player1.getManSize() - 1, &point);
        }else {
            SDL_Log("realloc failed in CreateManToMap player1");
        }

    }
}

void removeFirstManFromMap(bool isEnemy) {
    if (isEnemy) {
        if (player2.getManSize() == 0) return;

        map[player2.getManAt(0)->getPos()] = 0;

        player2.shiftManLeft();

        player2.setManSize(player2.getManSize() - 1);

        // Realloc - EGYSZERŰBB!
        if (!player2.reallocMan(player2.getManSize())) {
            SDL_Log("realloc failed in removeFirstManFromMap player2");
        }

        if (player2.getManSize() == 0) {
            player2.setMan(nullptr);
        }
    }else {
        SDL_Log("map torles");
        if (player1.getManSize() == 0) return;

        map[player1.getManAt(0)->getPos()] = 0;

        player1.shiftManLeft();

        player1.setManSize(player1.getManSize() - 1);

        // Realloc - EGYSZERŰBB!
        if (!player1.reallocMan(player1.getManSize())) {
            SDL_Log("realloc failed in removeFirstManFromMap player1");
        }

        if (player1.getManSize() == 0) {
            player1.setMan(nullptr);
        }
    }
}

void CreateManToPool(GameUnit unit, bool isEnemy) {
    if (isEnemy) {
        unit.setPos(mezoszam - 1);
        SDL_Log("enemy");
        player2.setPoolSize(player2.getPoolSize() + 1);
        player2.reallocPool(player2.getPoolSize());

        // uj ember beszurasa a tomb vegere
        player2.setPoolAt(player2.getPoolSize() - 1, &unit);
        SDL_Log("uj enemyPool letrehozva");
        SDL_Log(std::to_string(player2.getPoolAt(0)->getRect().x).c_str());
        SDL_Log(std::to_string(player2.getPoolAt(0)->getRect().y).c_str());
    }else {
        unit.setPos(0);
        player1.setPoolSize(player1.getPoolSize() + 1);

        player1.reallocPool(player1.getPoolSize());

        // uj ember beszurasa a tomb vegere
        player1.setPoolAt(player1.getPoolSize() - 1, &unit);
        SDL_Log("uj pool letrehozva");
        SDL_Log(std::to_string(player1.getPoolAt(0)->getRect().x).c_str());
        SDL_Log(std::to_string(player1.getPoolAt(0)->getRect().y).c_str());
    }
}

void removeFirstManFromPool(bool isEnemy) {
    if (isEnemy) {
        if (player2.getPoolSize() == 0) return;

        player2.shiftPoolLeft();

        player2.setPoolSize(player2.getPoolSize() - 1);

        player2.reallocPool(player2.getPoolSize());

        if (player2.getPoolSize() == 0) {
            player2.setPool(nullptr);
        }
    }else {
        SDL_Log("pool torles");
        if (player1.getPoolSize() == 0) return;

        player1.shiftPoolLeft();

        player1.setPoolSize(player1.getPoolSize() - 1);

        player1.reallocPool(player1.getPoolSize());

        if (player1.getPoolSize() == 0) {
            player1.setPool(nullptr);
        }
    }
}