#ifndef ALIEN_H
#define ALIEN_H

#include <memory>

#include "Enemy.h"

constexpr int ALIEN_FRAME_SIZE = 16;
constexpr int ALIEN_BASE_SPEED = 2;
constexpr int ALIEN_FRAME_COUNTER_MAX = ALIEN_BASE_SPEED * 15;

class Alien : public Enemy
{
private:
  // aliens have 2 animation frames
  bool currentFrame{};
  int frameCounter{};

public:
  Alien(std::string textureName, sf::Vector2f pos, int maxHp, int points);
  virtual ~Alien() = default;

  void move(sf::Vector2f offset);
};

typedef std::shared_ptr<Alien> AlienPtr;

#endif
