#include "Squid.h"
#include "Game.h"
#include "Bullet.h"
#include <random>

Squid::Squid(sf::Vector2f pos)
    : ShootingAlien("squid", pos, Squid_HP, Squid_POINTS)
{
    sprite.setColor(sf::Color(255, 255, 0));
}

void Squid::update()
{
    int randomNumber = std::rand() % 400 + 1;

    // Shoot if the random number is 130 (1 in 400 chance)
    if (randomNumber == 130)
    {
        this->shoot();
    }
}

void Squid::shoot()
{

    // Triple shot with different angles
    for (int i = 0; i < 3; ++i)
    {
        float angleOffset = static_cast<float>(i - 1) * 5.f;
        sf::Vector2f bulletVelocity = sf::Vector2f(angleOffset, 5.f);
        sf::Vector2f bulletPosition = sprite.getPosition();
        Game::getGame().pushBullet(std::make_shared<EnemyBullet>(bulletPosition, bulletVelocity, angleOffset * -9.f));
    }
}