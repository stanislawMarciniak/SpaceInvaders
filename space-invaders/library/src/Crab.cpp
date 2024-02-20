#include "Crab.h"

Crab::Crab(sf::Vector2f pos) : Alien("crab", pos, CRAB_HP, CRAB_POINTS)
{
  sprite.setColor(sf::Color(0, 255, 255));
}

void Crab::update()
{
  // NOOP
}
