#include <boost/test/unit_test.hpp>

#include "Shield.h"

BOOST_AUTO_TEST_SUITE(ShieldTest)

BOOST_AUTO_TEST_CASE(shield_creation_test)
{
    sf::Vector2f position(100.f, 200.f);
    Shield shield(position);

    BOOST_CHECK_EQUAL(shield.getCurrentHp(), SHIELD_HP);
    BOOST_CHECK_EQUAL(shield.isDead(), false);
}

BOOST_AUTO_TEST_CASE(shield_hit_test)
{
    sf::Vector2f position(100.f, 200.f);
    Shield shield(position);

    int initialHp = SHIELD_HP;

    shield.hit(1);
    BOOST_CHECK_EQUAL(shield.getCurrentHp(), initialHp - 1);
    BOOST_CHECK_EQUAL(shield.isDead(), false);

    for (int i = 1; i < initialHp; ++i)
    {
        shield.hit(1);
        BOOST_CHECK_EQUAL(shield.getCurrentHp(), initialHp - i - 1);
        BOOST_CHECK_EQUAL(shield.isDead(), i == initialHp - 1);
    }
}

BOOST_AUTO_TEST_SUITE_END()
