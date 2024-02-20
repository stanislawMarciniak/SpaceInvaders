#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>

#include "KillableEntity.h"

constexpr int PLAYER_RELOAD_TIME = 10;
constexpr int PLAYER_SPEED = 10;

class Player : public KillableEntity
{
private:
  float speed = PLAYER_SPEED;
  int reloadTimer{};
  int reloadTimeMax = PLAYER_RELOAD_TIME;

  void updateInput();
  void handleWindowCollision();
  void shoot();

public:
  Player(sf::Vector2f pos);
  ~Player();

  void update();
};

typedef std::shared_ptr<Player> PlayerPtr;

#endif