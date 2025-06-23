#ifndef GAMEUNIT_H
#define GAMEUNIT_H
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>


class GameUnit {
    int price{};
    int tipus{};
    int hp{};
    int range{};
    int dmg{};
    bool isEnemy;
    SDL_FRect rect{};
    SDL_Color color{};

public:
    GameUnit(int _tipus, int _hp, int _dmg, bool _isEnemy);
    GameUnit();

    int getPrice();
    int getTipus();
    int getHp();
    int getDmg();
    int getRange();
    SDL_FRect getRect();
    SDL_Color getColor();
    float getRextX();
    bool getIsEnemy();

    void setPrice(int _price);
    void setHp(int _hp);
    void setDmg(int _dmg);
    void setRange(int _range);
    void setRect(SDL_FRect _rect);
    void setColor(SDL_Color _color);
    void setRectX(float x);

    ~GameUnit() = default;
};



#endif //GAMEUNIT_H
