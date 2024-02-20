#ifndef KILLABLE_ENTITY_H
#define KILLABLE_ENTITY_H

#include "Entity.h"

class KillableEntity : public Entity
{
private:
  int maxHp{};
  int currentHp{};

public:
  KillableEntity(std::string textureName, sf::Vector2f pos, int maxHp);
  virtual ~KillableEntity() = default;

  void hit(int dmg);
  bool isDead();
  int getCurrentHp();
};

#endif