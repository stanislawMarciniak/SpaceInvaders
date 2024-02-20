#include "Game.h"
#include "Bullet.h"

Bullet::Bullet(
    std::string textureName,
    sf::Vector2f pos,
    sf::Vector2f velocity,
    float rot) : Entity(textureName, pos),
                 velocity{velocity}
{
  sprite.scale(0.6f, 0.6f);
  sprite.setRotation(rot);
}

void Bullet::update()
{
  sprite.move(velocity);

  if (isOutsideWindow())
    dead = true;

  checkCollisions();
}

bool Bullet::isDead() const
{
  return dead;
}

void Bullet::setDead(bool value)
{
  dead = value;
}

void Bullet::handleShieldCollisions()
{
  if (isDead())
    return;

  auto &shields = Game::getGame().getShields();
  for (auto it = shields.begin(); it != shields.end(); ++it)
  {
    auto &shield = *it;
    if (this->getBounds().intersects(shield->getBounds()))
    {
      setDead(true);
      shield->hit(1);

      if (shield->isDead())
      {
        it = shields.erase(it);
      }

      return;
    }
  }
}

/*
  Player Bullet
*/

PlayerBullet::PlayerBullet(sf::Vector2f pos, sf::Vector2f velocity) : Bullet("playerBullet", pos, velocity, -90.f) {}

void PlayerBullet::checkCollisions()
{
  if (isDead())
    return;

  auto enemyManager = Game::getGame().getEnemyManager();
  if (enemyManager)
  {
    // with aliens
    auto aliens = enemyManager->getAliens();
    for (auto &row : aliens)
    {
      for (auto &alien : row)
      {
        if (this->getBounds().intersects(alien->getBounds()))
        {
          setDead(true);
          alien->hit(1);
          return;
        }
      }
    }
  }

  // with ufo
  auto ufo = enemyManager->getUFO();
  if (ufo)
  {
    if (this->getBounds().intersects(ufo->getBounds()))
    {
      setDead(true);
      ufo->hit(1);
      return;
    }
  }

  // with other bullets
  const auto &bullets = Game::getGame().getBullets();
  for (const auto &bullet : bullets)
  {
    if (bullet.get() == this)
      continue;

    if (this->getBounds().intersects(bullet->getBounds()))
    {
      bullet->setDead(true);
      setDead(true);
      return;
    }
  }

  // with shields
  handleShieldCollisions();
}

/*
  Enemy Bullet
*/

EnemyBullet::EnemyBullet(sf::Vector2f pos, sf::Vector2f velocity, float angleOffset)
    : Bullet("enemyBullet", pos, velocity, 90.f + angleOffset) {}

void EnemyBullet::checkCollisions()
{
  if (isDead())
    return;

  auto player = Game::getGame().getPlayer();

  // Check collision with player
  if (this->getBounds().intersects(player->getBounds()))
  {
    player->hit(1);
    setDead(true);
    return;
  }

  handleShieldCollisions();
}
