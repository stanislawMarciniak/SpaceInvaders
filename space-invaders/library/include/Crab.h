#ifndef CRAB_H
#define CRAB_H

#include "Alien.h"

constexpr int CRAB_HP = 3;
constexpr int CRAB_POINTS = 15;

class Crab : public Alien
{
public:
  Crab(sf::Vector2f pos);
  virtual ~Crab() = default;

  void update();
};

#endif
