#include "ShootingAlien.h"

ShootingAlien::ShootingAlien(std::string textureName, sf::Vector2f pos, int maxHp, int points)
    : Alien(textureName, pos, maxHp, points)
{
}

ShootingAlien::~ShootingAlien() = default;
