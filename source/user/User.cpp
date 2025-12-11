#include "User.h"
#include "../tower/Tower.h"

User::User() : baseHp(50), xp(0), level(0), man(nullptr), manSize(0), pool(nullptr), poolSize(0) {

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
GameUnit* User::getManAt(int x) {
    return &man[x];
}
bool User::getManIsEmpty() {
    if (this->man == nullptr) {
        return true;
    }
    return false;
}
int User::getManSize() {
    return manSize;
}
GameUnit* User::getPool() {
    return pool;
}
GameUnit* User::getPoolAt(int x) {
    return &pool[x];
}
bool User::getPoolIsEmpty() {
    if (this->pool == nullptr) {
        return true;
    }
    return false;
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
void User::setManAt(int x, GameUnit *unit) {
    this->man[x] = *unit;
}
void User::setManSize(int manSize) {
    this->manSize = manSize;
}
void User::setPool(GameUnit *pool) {
    this->pool = pool;
}
void User::setPoolAt(int x, GameUnit *unit) {
    this->pool[x] = *unit;
}
void User::setPoolSize(int poolSize) {
    this->poolSize = poolSize;
}

// Realloc wrapperek
bool User::reallocMan(int newSize) {
    GameUnit* temp = (GameUnit*)realloc(man, newSize * sizeof(GameUnit));
    if (temp || newSize == 0) {
        man = temp;
        manSize = newSize;
        return true;
    }
    return false;
}

bool User::reallocPool(int newSize) {
    GameUnit* temp = (GameUnit*)realloc(pool, newSize * sizeof(GameUnit));
    if (temp || newSize == 0) {
        pool = temp;
        poolSize = newSize;
        return true;
    }
    return false;
}

// Shift helper (elemek előretolása)
void User::shiftManLeft() {
    for (int i = 1; i < manSize; i++) {
        man[i - 1] = man[i];
    }
}

void User::shiftPoolLeft() {
    for (int i = 1; i < poolSize; i++) {
        pool[i - 1] = pool[i];
    }
}

User::~User() {
    free(pool);
    free(man);
}