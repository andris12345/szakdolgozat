#ifndef TOWER_H
#define TOWER_H
#include <SDL3/SDL_rect.h>
#include "../variables/Variables.h"

class Tower {
    double dmg{};
    int range{};
    double cost{};
    int type{};
    SDL_FRect rect = {};
    SDL_Color color = {};
    SDL_Color hoverColor = {}; //todo: talan atrakni coverre hover helyett
    bool isHovered = false;
    bool isVisible = false;

public:
    Tower();
    Tower(double dmg, int range, double cost, int type, SDL_FRect rect, SDL_Color color, SDL_Color hoverColor);

    double getDmg();
    int getRange();
    double getCost();
    int getType();
    SDL_FRect& getRect();
    SDL_Color getColor();
    SDL_Color getHoverColor();
    bool getIsHovered();
    bool getIsVisible();

    void setDmg(double dmg);
    void setRange(int range);
    void setCost(double cost);
    void setType(int type);
    void setIsHovered(bool isHovered);
    void setIsVisible(bool isVisible);



};

void CreateNewTower(double dmg, int range, double cost, int type, SDL_FRect _rect, SDL_Color _color, SDL_Color _hoverColor, int pos);

void renderTower(SDL_Renderer* renderer, Tower& tower);

bool isMouseOver(Tower* Tower, float mouseX, float mouseY);


#endif //TOWER_H
