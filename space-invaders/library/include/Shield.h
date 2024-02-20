#ifndef SHIELD_H
#define SHIELD_H

#include "KillableEntity.h"

#include <memory>

constexpr int SHIELD_HP = 4;

class Shield : public KillableEntity
{
public:
  Shield(sf::Vector2f pos);
  virtual ~Shield() = default;

  void update();
};

using ShieldPtr = std::shared_ptr<Shield>;

#endif