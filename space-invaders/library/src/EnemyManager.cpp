#include <iostream>
#include <iterator>

#include "EnemyManager.h"
#include "Crab.h"
#include "Octopus.h"
#include "Squid.h"
#include "Game.h"

EnemyManager::EnemyManager() {}

std::list<std::list<AlienPtr>> &EnemyManager::getAliens()
{
  return aliens;
}

UFOPtr EnemyManager::getUFO()
{
  return ufo;
}

void EnemyManager::loadWave(std::vector<std::string> &levelLayout)
{
  aliens.clear();
  aliensSpeed = ALIEN_BASE_SPEED;

  int rowNumber = 0;

  std::list<std::list<AlienPtr>>::iterator currentRow;

  for (auto layoutRow : levelLayout)
  {
    // add new row
    aliens.push_back(std::list<AlienPtr>());

    if (!rowNumber)
    {
      currentRow = aliens.begin();
    }
    else
    {
      ++currentRow;
    }

    float y = rowNumber * 72.f + 128.f;

    // spawn aliens
    for (int i = 0; i < layoutRow.length(); ++i)
    {
      AlienPtr alien;
      float x = i * 72.f + 32.f;
      switch (layoutRow[i])
      {
      case 'c':
        alien = std::make_shared<Crab>(sf::Vector2f(x, y));
        break;
      case 's':
        alien = std::make_shared<Squid>(sf::Vector2f(x, y));
        break;
      case 'o':
        alien = std::make_shared<Octopus>(sf::Vector2f(x, y));
        break;
      default:
        // any other character is treated as a blank space
        continue;
      }

      // push alien to the list
      currentRow->push_back(alien);
    }

    ++rowNumber;
  }
}

void EnemyManager::update()
{
  updateAliens();
  updateUFO();
}

void EnemyManager::updateAliens()
{
  // go a step down and change direction if any of the aliens hit the wall
  bool hitWall = false;

  for (auto rowIt = aliens.begin(); rowIt != aliens.end();)
  {

    for (auto it = rowIt->begin(); it != rowIt->end();)
    {
      auto &alien = *it;
      alien->update();

      if (alien->isDead())
      {
        Game::getGame().addPoints(alien->getPoints());
        it = rowIt->erase(it);
        aliensSpeed += aliensSpeed > 0 ? 0.3 : -0.3;
        continue;
      }

      ++it;
    }

    if (rowIt->empty())
    {
      rowIt = aliens.erase(rowIt);
      continue;
    }

    // check if any of the aliens at front and back of row hit a wall
    if (!hitWall)
    {
      if (aliensSpeed > 0 && rowIt->back()->isOutsideWindow())
      { // moving right
        hitWall = true;
      }
      else if (rowIt->front()->isOutsideWindow())
      {
        hitWall = true;
      }
    }

    ++rowIt;
  }

  // if no rows left - start the next level
  if (aliens.empty())
  {
    Game::getGame().nextLevel();
    return;
  }

  // check if the last row crossed the gameOver line
  auto gameOverLine = Game::getGame().getRenderTarget().getView().getSize().y - 100.f;
  for (auto it = aliens.back().begin(); it != aliens.back().end(); ++it)
  {
    auto bounds = (*it)->getBounds();
    if (bounds.top + bounds.height > gameOverLine)
    {
      Game::getGame().gameOver();
    }
  }

  if (hitWall)
    aliensSpeed *= -1;

  for (auto &row : aliens)
    for (auto &alien : row)
      alien->move(sf::Vector2f(aliensSpeed, hitWall ? 32.f : 0.f));
}

void EnemyManager::updateUFO()
{
  if (ufo)
  {
    ufo->update();
    if (ufo->isDead())
    {
      Game::getGame().addPoints(ufo->getPoints());
      ufo = nullptr;
      return;
    }

    // ufo left the screen = no points
    if (ufo->isOutsideWindow())
    {
      ufo = nullptr;
    }

    return;
  }

  if (ufoSpawnTimer < UFO_SPAWN_COOLDOWN)
  {
    ++ufoSpawnTimer;
    return;
  }

  // no ufo and it's time to spawn a new one!

  // reset timer
  ufoSpawnTimer = 0;
  // spawn ufo
  bool spawnFromLeft = std::rand() % 2;
  ufo = std::make_shared<UFO>(spawnFromLeft);
}

void EnemyManager::draw()
{
  for (auto row : aliens)
    for (auto alien : row)
      alien->draw();

  if (ufo)
    ufo->draw();
}
