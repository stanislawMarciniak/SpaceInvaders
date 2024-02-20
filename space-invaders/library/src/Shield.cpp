#include "Shield.h"

Shield::Shield(sf::Vector2f pos) : KillableEntity("shield", pos, SHIELD_HP)
{
    sprite.setColor(sf::Color(0, 255, 0));
    sprite.setScale(0.2f, 0.2f);
}

void Shield::update()
{
    // NOOP
}
