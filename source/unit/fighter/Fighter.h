#ifndef FIGHTER_H
#define FIGHTER_H



class Fighter {
    int hp{};
    int range{};
    int dmg{};

    public:
    Fighter();
    Fighter(int _hp, int _dmg);

    int getHp();
    int getDmg();
    int getRange();

    void setHp(int _hp);
    void setDmg(int _dmg);
    void setRange(int _range);
};



#endif //FIGHTER_H
