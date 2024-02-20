#include "Enemy.h"

Enemy::Enemy(std::string textureName, sf::Vector2f pos, int maxHp, int points) : KillableEntity(textureName, pos, maxHp), points{points} {}

int Enemy::getPoints()
{
  return points;
}
