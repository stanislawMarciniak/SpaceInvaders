#ifndef ENEMY_H
#define ENEMY_H

#include "KillableEntity.h"

class Enemy : public KillableEntity
{
private:
  int points{};

public:
  Enemy(std::string textureName, sf::Vector2f pos, int maxHp, int points);
  virtual ~Enemy() = default;

  int getPoints();
};

#endif
