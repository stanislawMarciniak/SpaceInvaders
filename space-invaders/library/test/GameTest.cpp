#include <boost/test/unit_test.hpp>

#include "Game.h"

BOOST_AUTO_TEST_SUITE(GameTest)

BOOST_AUTO_TEST_CASE(game_initialization_test)
{
    Game &game = Game::getGame();

    BOOST_CHECK_EQUAL(game.getPoints(), 0);
    BOOST_CHECK_EQUAL(game.getHighscore(), 0);
    BOOST_CHECK_EQUAL(game.getLevel(), 0);
    BOOST_CHECK_EQUAL(game.getGameState(), GameState::StartScreen);
}

BOOST_AUTO_TEST_CASE(game_bullet_handling_test)
{
    Game &game = Game::getGame();

    auto enemyBullet = std::make_shared<EnemyBullet>(sf::Vector2f(100.f, 200.f), sf::Vector2f(2.f, 3.f), 45.f);
    game.pushBullet(enemyBullet);

    const std::vector<BulletPtr> &bullets = game.getBullets();
    BOOST_REQUIRE_EQUAL(bullets.size(), 1);
}

BOOST_AUTO_TEST_CASE(game_add_points_test)
{
    Game &game = Game::getGame();

    game.addPoints(100);

    BOOST_CHECK_EQUAL(game.getPoints(), 100);
}

BOOST_AUTO_TEST_SUITE_END()
