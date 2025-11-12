#include "Tower.h"

Tower::Tower( double _dmg, int _range, double _cost,int _type, SDL_FRect _rect, SDL_Color _color, SDL_Color _hoverColor):  dmg(_dmg), range(_range), cost(_cost), type(_type), rect(_rect), color(_color), hoverColor(_hoverColor){ }

Tower::Tower() = default;

double Tower::getCost() { return cost; }
double Tower::getDmg() { return dmg; }
int Tower::getRange() { return range; }
int Tower::getType() { return type; }
SDL_FRect& Tower::getRect() { return rect; }
SDL_Color Tower::getColor() { return color; }
SDL_Color Tower::getHoverColor() { return hoverColor; }
bool Tower::getIsHovered() { return isHovered; }
bool Tower::getIsVisible() { return isVisible; }



void Tower::setDmg(double _dmg) { dmg = _dmg; }
void Tower::setRange(int _range) { range = _range; }
void Tower::setCost(double _cost) { cost = _cost; }
void Tower::setType(int _type) { type = _type; }
void Tower::setIsHovered(bool _isHovered) { isHovered = _isHovered; }
void Tower::setIsVisible(bool _isVisible) { isVisible = _isVisible; }


void CreateNewTower( double dmg, int range, double cost, int type, SDL_FRect _rect, SDL_Color _color, SDL_Color _hoverColor, int pos) {
    towerNumber++;
    Tower t = Tower(dmg, range, cost, type, _rect, _color, _hoverColor);
    t.setIsVisible(true);
    towers[pos] = t;
}

bool isMouseOver(Tower* tower, float mouseX, float mouseY) {
    if (!tower) return false;
    return (mouseX >= tower->getRect().x && mouseX <= tower->getRect().x + tower->getRect().w &&
            mouseY >= tower->getRect().y && mouseY <= tower->getRect().y + tower->getRect().h);
}

void renderTower(SDL_Renderer *renderer, Tower& tower) {
    float x, y;
    SDL_GetMouseState(&x, &y);

    if (isMouseOver(&tower, x, y)) {
        SDL_SetRenderDrawColor(renderer, tower.getHoverColor().r, tower.getHoverColor().g, tower.getHoverColor().b, 255);
    }else {
        SDL_SetRenderDrawColor(renderer, tower.getColor().r, tower.getColor().g, tower.getColor().b, 255);
    }
    SDL_RenderFillRect(renderer, &tower.getRect());
}