#ifndef TOWER_H
#define TOWER_H
#include <SDL3/SDL_rect.h>
#include "../variables/Variables.h"

class Tower {
    bool exists = false;
    double dmg{};
    int range{};
    double cost{};
    int type{};
    int pos{};
    SDL_FRect rect = {};
    SDL_Color color = {};
    SDL_Color hoverColor = {}; //todo: talan atrakni coverre hover helyett
    bool isHovered = false;
    bool isVisible = false;

public:
    Tower();
    Tower(double dmg, int range, double cost, int type, SDL_FRect rect, SDL_Color color, SDL_Color hoverColor);

    bool isExists();
    double getDmg();
    int getRange();
    double getCost();
    int getType();
    int getPos();
    SDL_FRect& getRect();
    SDL_Color getColor();
    SDL_Color getHoverColor();
    bool getIsHovered();
    bool getIsVisible();

    void setRect(SDL_FRect _rect);
    void setColor(SDL_Color _color);
    void setHoverColor(SDL_Color _hoverColor);
    void setExists(bool exists);
    void setDmg(double dmg);
    void setRange(int range);
    void setCost(double cost);
    void setType(int type);
    void setPos(int pos);
    void setIsHovered(bool isHovered);
    void setIsVisible(bool isVisible);

    void resetTower();
    void setTower(Tower tower);

};

void CreateNewTower( int _type, int _pos, bool _client);

void renderTower(SDL_Renderer* renderer, Tower& tower);

bool isMouseOver(Tower* Tower, float mouseX, float mouseY);

void resetTower();

#endif //TOWER_H
