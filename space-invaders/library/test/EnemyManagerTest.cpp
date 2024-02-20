#include <boost/test/unit_test.hpp>

#include "EnemyManager.h"

BOOST_AUTO_TEST_SUITE(EnemyManagerTests)

BOOST_AUTO_TEST_CASE(enemy_manager_initialization_test)
{
    EnemyManager enemyManager;

    std::list<std::list<AlienPtr>> &aliens = enemyManager.getAliens();
    UFOPtr ufo = enemyManager.getUFO();

    BOOST_CHECK(aliens.empty());
    BOOST_CHECK_EQUAL(ufo, nullptr);
}

BOOST_AUTO_TEST_CASE(enemy_manager_load_wave_test)
{
    EnemyManager enemyManager;

    std::vector<std::string> levelLayout = {
        "cso",
        "oso",
        "cso"};

    enemyManager.loadWave(levelLayout);

    std::list<std::list<AlienPtr>> &aliens = enemyManager.getAliens();

    BOOST_CHECK(!aliens.empty());
    BOOST_CHECK_EQUAL(aliens.size(), 3);
    BOOST_CHECK_EQUAL(aliens.front().size(), 3);
}

BOOST_AUTO_TEST_SUITE_END()
