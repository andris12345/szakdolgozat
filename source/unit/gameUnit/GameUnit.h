#ifndef GAMEUNIT_H
#define GAMEUNIT_H
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>


class GameUnit {
    int hp{};
    int range{};
    int dmg{};
    SDL_FRect rect{};
    SDL_Color color{};

public:
    GameUnit();
    GameUnit(int _hp, int _dmg);

    int getHp();
    int getDmg();
    int getRange();
    SDL_FRect getRect();
    SDL_Color getColor();

    void setHp(int _hp);
    void setDmg(int _dmg);
    void setRange(int _range);
    void setRect(SDL_FRect _rect);
    void setColor(SDL_Color _color);

    ~GameUnit() = default;
};



#endif //GAMEUNIT_H
