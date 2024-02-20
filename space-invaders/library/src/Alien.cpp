#include "Alien.h"
#include "Game.h"

Alien::Alien(std::string textureName, sf::Vector2f pos, int maxHp, int points) : Enemy(textureName, pos, maxHp, points)
{
  sprite.scale(4, 4);
  sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
  // after setting texture rect we have to reset sprite origin to center
  sprite.setOrigin(
      sf::Vector2f(
          sprite.getLocalBounds().width * 0.5f,
          sprite.getLocalBounds().height * 0.5f));
}

void Alien::move(sf::Vector2f offset)
{
  frameCounter += abs(offset.x);
  if (frameCounter > ALIEN_FRAME_COUNTER_MAX)
  {
    currentFrame = !currentFrame;
    frameCounter = 0;
  }

  // animation
  sprite.setTextureRect(sf::IntRect(currentFrame * ALIEN_FRAME_SIZE, 0, ALIEN_FRAME_SIZE, ALIEN_FRAME_SIZE));
  sprite.move(offset);
}
