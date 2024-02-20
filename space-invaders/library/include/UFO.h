#ifndef UFO_H
#define UFO_H

#include <memory>

#include "Enemy.h"

constexpr int UFO_HP = 1;
constexpr int UFO_BASE_SPEED = 3;
constexpr int UFO_MIN_POINTS = 50;
constexpr int UFO_MAX_POINTS = 300;

class UFO : public Enemy
{
private:
  int speed = UFO_BASE_SPEED;

public:
  // UFO can be either spawned from right or left side
  UFO(bool fromLeft);
  ~UFO() = default;

  void update();
  // override Entity function, because we want the UFO to disappear after leaving the screen
  bool isOutsideWindow();
};

typedef std::shared_ptr<UFO> UFOPtr;

int getUFOPoints();

#endif
