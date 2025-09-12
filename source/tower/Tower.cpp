#include "Tower.h"

Tower::Tower(int _dmg, int _range, int _cost, int pos): dmg(_dmg), range(_range), cost(_cost) {
    switch (pos) {
        case 1:
            rect =  {.x = 60, .y = (emberKezdoY - 100), .w = 20, .h = 20};
            break;
        case 2:
            rect =  {.x = 60, .y = (emberKezdoY - 120), .w = 20, .h = 20};
            break;
        default:
            break;
    }

}

Tower::Tower() = default; //todo: atrakni ide is a gomb ismouseover + render

int Tower::getCost() const { return cost; }
int Tower::getDmg() const { return dmg; }
int Tower::getRange() const { return range; }

void Tower::setDmg(int _dmg) { dmg = _dmg; }
void Tower::setRange(int _range) { range = _range; }
void Tower::setCost(int _cost) { cost = _cost; }