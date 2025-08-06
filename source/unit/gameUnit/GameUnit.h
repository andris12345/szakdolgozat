#ifndef GAMEUNIT_H
#define GAMEUNIT_H
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>


class GameUnit {
    float price{};
    int tipus{};
    int hp{};
    int maxHp{};
    int range{};
    int dmg{};
    int poz{};
    bool isEnemy;
    SDL_FRect rect{};
    SDL_Color color{};

public:
    GameUnit(int _tipus, int _hp, int _dmg, bool _isEnemy);
    GameUnit();

    float getPrice();
    int getTipus();
    int getHp();
    int getMaxHp();
    int getDmg();
    int getRange();
    int getPos();
    SDL_FRect getRect();
    SDL_Color getColor();
    float getRextX();
    bool getIsEnemy();

    void setPrice(float _price);
    void setHp(int _hp);
    void setMaxHp(int _maxHp);
    void setDmg(int _dmg);
    void setRange(int _range);
    void setPos(int _pos);
    void setRect(SDL_FRect _rect);
    void setColor(SDL_Color _color);
    void setRectX(float x);

    ~GameUnit() = default;
};



#endif //GAMEUNIT_H
