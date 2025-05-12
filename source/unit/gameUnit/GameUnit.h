#ifndef GAMEUNIT_H
#define GAMEUNIT_H
#include <SDL3/SDL_rect.h>


class GameUnit {
    int hp{};
    int range{};
    int dmg{};
    SDL_FRect rect{};

public:
    GameUnit();
    GameUnit(int _hp, int _dmg);

    int getHp();
    int getDmg();
    int getRange();

    void setHp(int _hp);
    void setDmg(int _dmg);
    void setRange(int _range);

    ~GameUnit() = default;
};



#endif //GAMEUNIT_H
