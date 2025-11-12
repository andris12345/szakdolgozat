#ifndef GAMEUNIT_H
#define GAMEUNIT_H
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

#include "../../variables/Variables.h"

class GameUnit {
    double price{};
    int tipus{};
    double hp{};
    double maxHp{};
    int range{};
    double dmg{};
    int poz{};
    double xp{};
    bool isEnemy;
    SDL_FRect rect{};
    SDL_Color color{};

public:
    GameUnit(int _tipus, int _hp, int _dmg, bool _isEnemy);
    GameUnit();

    double getPrice();
    int getTipus();
    double getHp();
    double getMaxHp();
    double getDmg();
    int getRange();
    int getPos();
    double getXp();
    SDL_FRect getRect();
    SDL_Color getColor();
    float getRextX();
    bool getIsEnemy();

    void setPrice(double _price);
    void setHp(double _hp);
    void setMaxHp(double _maxHp);
    void setDmg(double _dmg);
    void setRange(int _range);
    void setPos(int _pos);
    void setXp(double _xp);
    void setRect(SDL_FRect _rect);
    void setColor(SDL_Color _color);
    void setRectX(float x);

    ~GameUnit() = default;
};



#endif //GAMEUNIT_H
