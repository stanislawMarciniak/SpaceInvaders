#include <random>

#include "UFO.h"
#include "Game.h"

UFO::UFO(bool fromLeft) : Enemy("ufo", sf::Vector2f(fromLeft ? 0.f : Game::getGame().getRenderTarget().getView().getSize().x, 64.f), UFO_HP, getUFOPoints())
{
  sprite.scale(0.1, 0.1);
  speed *= fromLeft ? 1 : -1;
}

void UFO::update()
{
  sprite.move(speed, 0.f);
}

bool UFO::isOutsideWindow()
{
  auto pos = sprite.getPosition();
  auto viewSize = Game::getGame().getRenderTarget().getView().getSize();
  auto bounds = getBounds();

  // fully outside window
  return pos.x + bounds.width / 2 < 0.f ||
         pos.x - bounds.width / 2 > viewSize.x ||
         pos.y + bounds.height / 2 < 0.f ||
         pos.y - bounds.height / 2 > viewSize.y;
}

int getUFOPoints()
{
  std::random_device rd;                                                 // obtain a random number from hardware
  std::mt19937 gen(rd());                                                // seed the generator
  std::uniform_int_distribution<> distr(UFO_MIN_POINTS, UFO_MAX_POINTS); // define the range

  return distr(gen);
}
