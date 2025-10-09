#ifndef TOWER_H
#define TOWER_H
#include <SDL3/SDL_rect.h>
#include "../variables/Variables.h"

class Tower {
    int dmg{};
    int range{};
    int cost{};
    int type{};
    SDL_FRect rect = {};
    SDL_Color color = {};
    SDL_Color hoverColor = {}; //todo: talan atrakni coverre hover helyett
    bool isHovered = false;
    bool isVisible = false;

public:
    Tower();
    Tower(int dmg, int range, int cost, int type, SDL_FRect rect, SDL_Color color, SDL_Color hoverColor);

    int getDmg();
    int getRange();
    int getCost();
    int getType();
    SDL_FRect& getRect();
    SDL_Color getColor();
    SDL_Color getHoverColor();
    bool getIsHovered();
    bool getIsVisible();

    void setDmg(int dmg);
    void setRange(int range);
    void setCost(int cost);
    void setType(int type);
    void setIsHovered(bool isHovered);
    void setIsVisible(bool isVisible);



};

void CreateNewTower(int dmg, int range, int cost, int type, SDL_FRect _rect, SDL_Color _color, SDL_Color _hoverColor, int pos);

void renderTower(SDL_Renderer* renderer, Tower& tower);

bool isMouseOver(Tower* Tower, float mouseX, float mouseY);


#endif //TOWER_H
