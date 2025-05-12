#ifndef TANK_H
#define TANK_H



class Tank {
    int hp{};
    int range{};
    int dmg{};

public:
    Tank();
    Tank(int _hp, int _dmg);

    int getHp();
    int getDmg();
    int getRange();

    void setHp(int _hp);
    void setDmg(int _dmg);
    void setRange(int _range);
};



#endif //TANK_H
