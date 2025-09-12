#ifndef TOWER_H
#define TOWER_H
#include <SDL3/SDL_rect.h>
#include "../variables/Variables.h"


class Tower {
    int dmg{};
    int range{};
    int cost{};
    SDL_FRect rect{};
    SDL_Color color{};
    SDL_Color hoverColor{};

public:
    Tower();
    Tower(int dmg, int range, int cost, int pos);

    int getDmg() const;
    int getRange() const;
    int getCost() const;

    void setDmg(int dmg);
    void setRange(int range);
    void setCost(int cost);
};



#endif //TOWER_H
