#include "KillableEntity.h"
#include <iostream>

KillableEntity::KillableEntity(std::string textureName, sf::Vector2f pos, int maxHp) : Entity(textureName, pos), maxHp{maxHp}, currentHp{maxHp} {}

void KillableEntity::hit(int dmg)
{
  currentHp -= dmg;
  // make the entity more transparent after each hit, indicating it's about to die
  auto currentColor = sprite.getColor();
  sf::Color newColor(currentColor.r, currentColor.g, currentColor.b, currentColor.a * 0.6);
  sprite.setColor(newColor);
}

bool KillableEntity::isDead()
{
  return currentHp <= 0;
}

int KillableEntity::getCurrentHp()
{
  return currentHp;
}
