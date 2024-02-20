#include <ctime>
#include "Game.h"

int main()
{
  std::srand(std::time(0));

  Game &game = Game::getGame();

  game.run();

  return 0;
}