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
  float money;
  std::array<std::unique_ptr<Tower>, 2> towers;
  GameUnit *man;
  int manSize;
  GameUnit *pool;
  int poolSize;

public:
  User();

  User(float baseHp);

  User &operator=(const User &);


  float getBaseHp();
  float getXp();
  int getLevel();
  float getMoney();
  Tower* getTowerAt(int x);
  GameUnit* getMan();
  GameUnit* getManAt(int x);
  bool getManIsEmpty();
  int getManSize();
  GameUnit* getPool();
  GameUnit* getPoolAt(int x);
  bool getPoolIsEmpty();
  int getPoolSize();

  void setBaseHp(float baseHp);
  void setXp(float xp);
  void setLevel(int level);
  void setMoney(float money);
  void setTowerAt(int x, std::unique_ptr<Tower> tower);
  void setMan(GameUnit *man);
  void setManAt(int x, GameUnit *unit);
  void setManSize(int manSize);
  void setPool(GameUnit *pool);
  void setPoolAt(int x, GameUnit *unit);
  void setPoolSize(int poolSize);

  // Realloc wrapperek
  bool reallocMan(int newSize);
  bool reallocPool(int newSize);

  // Shift helper (elemek előretolása)
  void shiftManLeft();
  void shiftPoolLeft();

  std::string toString();

  ~User();
  };



#endif //USER_H
