#ifndef RANGED_H
#define RANGED_H



class Ranged {
    int hp{};
    int range{};
    int dmg{};

public:
    Ranged();
    Ranged(int _hp, int _dmg);

    int getHp();
    int getDmg();
    int getRange();

    void setHp(int _hp);
    void setDmg(int _dmg);
    void setRange(int _range);
};



#endif //RANGED_H
