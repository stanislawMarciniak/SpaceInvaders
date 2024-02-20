#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Alien.h"
#include "UFO.h"
#include <list>

constexpr int UFO_SPAWN_COOLDOWN = 450; // 30 fps * 15 = 15 seconds

class EnemyManager
{
private:
  std::list<std::list<AlienPtr>> aliens;
  float aliensSpeed{};

  UFOPtr ufo;
  int ufoSpawnTimer{};

  void updateAliens();
  void updateUFO();

public:
  EnemyManager();
  ~EnemyManager() = default;

  std::list<std::list<AlienPtr>> &getAliens();
  UFOPtr getUFO();
  void loadWave(std::vector<std::string> &levelLayout);
  void update();
  void draw();
};

typedef std::shared_ptr<EnemyManager> EnemyManagerPtr;

#endif
