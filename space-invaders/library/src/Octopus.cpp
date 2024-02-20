#include "Octopus.h"
#include "Game.h"
#include "Bullet.h"
#include <cstdlib>
#include <ctime>

Octopus::Octopus(sf::Vector2f pos)
    : ShootingAlien("octopus", pos, Octopus_HP, Octopus_POINTS)
{
    sprite.setColor(sf::Color(255, 0, 255));
}

void Octopus::update()
{
    int randomNumber = std::rand() % 400 + 1;

    // Shoot if the random number is 70 (1 in 400 chance)
    if (randomNumber == 70)
    {
        this->shoot();
    }
}

void Octopus::shoot()
{
    sf::Vector2f bulletVelocity = sf::Vector2f(0.f, 5.f);
    Game::getGame().pushBullet(std::make_shared<EnemyBullet>(sprite.getPosition(), bulletVelocity));
}
