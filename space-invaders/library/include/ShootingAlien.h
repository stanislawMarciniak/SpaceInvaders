#ifndef SHOOTING_ALIEN_H
#define SHOOTING_ALIEN_H

#include "Alien.h"
#include "Bullet.h"

class ShootingAlien : public Alien
{

public:
    ShootingAlien(std::string textureName, sf::Vector2f pos, int maxHp, int points);
    virtual ~ShootingAlien();

    virtual void shoot() = 0;
};

#endif
