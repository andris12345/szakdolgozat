#include "Tower.h"

Tower::Tower( double _dmg, int _range, double _cost,int _type, SDL_FRect _rect, SDL_Color _color, SDL_Color _hoverColor):  dmg(_dmg), range(_range), cost(_cost), type(_type), rect(_rect), color(_color), hoverColor(_hoverColor){ }

Tower::Tower() = default;

bool Tower::isExists() { return exists; }
double Tower::getCost() { return cost; }
double Tower::getDmg() { return dmg; }
int Tower::getRange() { return range; }
int Tower::getType() { return type; }
int Tower::getPos() { return pos; }

SDL_FRect& Tower::getRect() { return rect; }
SDL_Color Tower::getColor() { return color; }
SDL_Color Tower::getHoverColor() { return hoverColor; }
bool Tower::getIsHovered() { return isHovered; }
bool Tower::getIsVisible() { return isVisible; }
void Tower::setRect(SDL_FRect _rect) { rect = _rect;}
void Tower::setColor(SDL_Color _color) {color = _color;}
void Tower::setHoverColor(SDL_Color _hoverColor) {hoverColor = _hoverColor;}
void Tower::setExists(bool _exists) { exists = _exists; }
void Tower::setDmg(double _dmg) { dmg = _dmg; }
void Tower::setRange(int _range) { range = _range; }
void Tower::setCost(double _cost) { cost = _cost; }
void Tower::setType(int _type) { type = _type; }
void Tower::setPos(int _pos) { pos = _pos; }
void Tower::setIsHovered(bool _isHovered) { isHovered = _isHovered; }
void Tower::setIsVisible(bool _isVisible) { isVisible = _isVisible; }


void Tower::resetTower() { *this = Tower(); }
void Tower::setTower(Tower tower) {
    *this = tower;
}


void CreateNewTower(int type, int pos, bool _client) {
    // Melyik player?
    User& targetPlayer = _client ? player2 : player1;

    // Melyik holder?
    Gomb* holder = (pos == 0) ? tower1Holder : tower2Holder;

    // Rect kiszámítása
    SDL_FRect towerRect = holder->getRect();

    // Ha kliens, akkor tükrözzük a koordinátákat
    if (_client) {
        float mirrorCenter = 300.0f;  // Vagy ami a tükrözési pont
        towerRect.x = (2.0f * mirrorCenter - towerRect.x) - towerRect.w;
    }

    // Színek típus alapján
    SDL_Color color = (type == 1)
        ? SDL_Color{238, 130, 238, 255}
    : SDL_Color{255, 255, 0, 255};

    SDL_Color hoverColor = (type == 1)
        ? SDL_Color{186, 85, 211, 255}
    : SDL_Color{204, 204, 0, 255};

    Tower t(
        (1 + 1 * targetPlayer.getLevel() * 0.25),
        3,
        (10 + 10 * targetPlayer.getLevel() * 0.25),
        type,
        towerRect,
        color,
        hoverColor
    );
    t.setExists(true);
    t.setIsVisible(true);

    targetPlayer.getTowerAt(pos)->setTower(t);
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