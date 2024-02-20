#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include <memory>

const sf::Vector2f PLAYER_BULLET_VELOCITY = sf::Vector2f(0.f, -20.f);

class Bullet : public Entity
{
protected:
  bool dead = false; // dead bullets are removed after each update
  sf::Vector2f velocity{};
  void handleShieldCollisions();

public:
  Bullet(std::string textureName, sf::Vector2f pos, sf::Vector2f velocity, float rot);
  virtual ~Bullet() = default;

  void update();
  virtual void checkCollisions() = 0;

  bool isDead() const;
  void setDead(bool value);
};

typedef std::shared_ptr<Bullet> BulletPtr;

class PlayerBullet : public Bullet
{
public:
  PlayerBullet(sf::Vector2f pos, sf::Vector2f velocity);
  ~PlayerBullet() = default;

  void checkCollisions();
};

typedef std::shared_ptr<PlayerBullet> PlayerBulletPtr;

class EnemyBullet : public Bullet
{
public:
  EnemyBullet(sf::Vector2f pos, sf::Vector2f velocity, float angleOffset = 0.0f);
  ~EnemyBullet() = default;

  void checkCollisions();
};

typedef std::shared_ptr<EnemyBullet> EnemyBulletPtr;

#endif