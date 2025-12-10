#include "User.h"
#include "../tower/Tower.h"

User::User() : baseHp(0), xp(0), level(0), man(nullptr), manSize(0), pool(nullptr), poolSize(0) {

}

User::User(float baseHp) : baseHp(baseHp), xp(0), level(0), man(nullptr), manSize(0), pool(nullptr), poolSize(0) {

}

//getterek
float User::getBaseHp() {
    return baseHp;
}
float User::getXp() {
    return xp;
}
int User::getLevel() {
    return level;
}
Tower* User::getTowerAt(int x) {
    return towers[x].get();
}
GameUnit* User::getMan() {
    return man;
}
int User::getManSize() {
    return manSize;
}
GameUnit* User::getPool() {
    return pool;
}
int User::getPoolSize() {
    return poolSize;
}

void User::setBaseHp(float baseHp) {
    this->baseHp = baseHp;
}

//setterek
void User::setXp(float xp) {
    this->xp = xp;
}

void User::setLevel(int level) {
    this->level = level;
}

void User::setTowerAt(int x, std::unique_ptr<Tower> tower) {
    this->towers[x] = std::move(tower);

}

void User::setMan(GameUnit *man) {
    this->man = man;
}

void User::setManSize(int manSize) {
    this->manSize = manSize;
}

void User::setPool(GameUnit *pool) {
    this->pool = pool;
}

void User::setPoolSize(int poolSize) {
    this->poolSize = poolSize;
}

User::~User() {
}