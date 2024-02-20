#include "Game.h"
#include "Player.h"

Player::Player(sf::Vector2f pos) : KillableEntity("player", pos, 3)
{
  sprite.scale(0.1f, 0.1f);
}

Player::~Player() {}

void Player::update()
{
  updateInput();
  handleWindowCollision();
}

void Player::updateInput()
{
  // Horizontal movement
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    sprite.move(-speed, 0.f);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    sprite.move(speed, 0.f);
  }

  if (reloadTimer > 0)
  {
    --reloadTimer;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  {
    shoot();

    reloadTimer = reloadTimeMax;
  }
}

void Player::handleWindowCollision()
{
  const sf::View &view = Game::getGame().getRenderTarget().getView();
  // Left
  if (sprite.getPosition().x <= 0.f)
    sprite.setPosition(view.getSize().x - getBounds().width / 2.f - 1.f, sprite.getPosition().y);
  // Right
  else if (sprite.getPosition().x >= view.getSize().x)
    sprite.setPosition(1.f, sprite.getPosition().y);
}

void Player::shoot()
{
  Game::getGame().pushBullet(std::make_shared<PlayerBullet>(sprite.getPosition(), PLAYER_BULLET_VELOCITY));
}
