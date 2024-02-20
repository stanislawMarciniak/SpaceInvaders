#ifndef OCTOPUS_H
#define OCTOPUS_H

#include "ShootingAlien.h"

constexpr int Octopus_HP = 2;
constexpr int Octopus_POINTS = 20;

class Octopus : public ShootingAlien
{
public:
  Octopus(sf::Vector2f pos);
  virtual ~Octopus() = default;

  void update();
  void shoot();
};

#endif
