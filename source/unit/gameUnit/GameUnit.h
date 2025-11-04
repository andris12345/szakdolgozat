#ifndef GAMEUNIT_H
#define GAMEUNIT_H
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

#include "../../variables/Variables.h"

class GameUnit {
    float price{};
    int tipus{};
    float hp{};
    float maxHp{};
    int range{};
    float dmg{};
    int poz{};
    float xp{};
    bool isEnemy;
    SDL_FRect rect{};
    SDL_Color color{};

public:
    GameUnit(int _tipus, int _hp, int _dmg, bool _isEnemy);
    GameUnit();

    float getPrice();
    int getTipus();
    float getHp();
    float getMaxHp();
    float getDmg();
    int getRange();
    int getPos();
    float getXp();
    SDL_FRect getRect();
    SDL_Color getColor();
    float getRextX();
    bool getIsEnemy();

    void setPrice(float _price);
    void setHp(float _hp);
    void setMaxHp(float _maxHp);
    void setDmg(float _dmg);
    void setRange(int _range);
    void setPos(int _pos);
    void setXp(float _xp);
    void setRect(SDL_FRect _rect);
    void setColor(SDL_Color _color);
    void setRectX(float x);

    ~GameUnit() = default;
};



#endif //GAMEUNIT_H
