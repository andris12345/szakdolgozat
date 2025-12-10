#ifndef USER_H
#define USER_H

#include <array>
#include <memory>

class Tower;
class GameUnit;

class User {
  float baseHp;
  float xp;
  int level;
  std::array<std::unique_ptr<Tower>, 2> towers;
  GameUnit *man;
  int manSize;
  GameUnit *pool;
  int poolSize;

public:
  User();

  User(float baseHp);




  float getBaseHp();
  float getXp();
  int getLevel();
  Tower* getTowerAt(int x);
  GameUnit* getMan();
  int getManSize();
  GameUnit* getPool();
  int getPoolSize();

  void setBaseHp(float baseHp);
  void setXp(float xp);
  void setLevel(int level);
  void setTowerAt(int x, std::unique_ptr<Tower> tower);
  void setMan(GameUnit *man);
  void setManSize(int manSize);
  void setPool(GameUnit *pool);
  void setPoolSize(int poolSize);

  ~User();
  };



#endif //USER_H
