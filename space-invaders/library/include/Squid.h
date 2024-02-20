#ifndef SQUID_H
#define SQUID_H

#include "ShootingAlien.h"

constexpr int Squid_HP = 1;
constexpr int Squid_POINTS = 25;

class Squid : public ShootingAlien
{
public:
    Squid(sf::Vector2f pos);
    virtual ~Squid() = default;

    void update();
    void shoot();
};

#endif
