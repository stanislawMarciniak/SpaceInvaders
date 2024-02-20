#ifndef GAME_H
#define GAME_H

#include <map>
#include <iostream>
#include <ctime>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "HUD.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Storage.h"
#include "Shield.h"

enum GameState
{
  Running = 0,
  Paused,
  GameOver,
  ScoreInput,
  StartScreen,
  Leaderboard
};

/*
  Class that acts as a game engine.
*/

typedef std::shared_ptr<sf::Texture> TexturePtr;

class Game
{
private:
  GameState gameState = GameState::StartScreen;
  // needed for menu navigation
  GameState prevGameState = GameState::StartScreen;

  std::shared_ptr<sf::RenderWindow> window;
  sf::VideoMode videoMode;
  sf::View view;
  sf::Event ev;
  void initWindow();

  std::map<std::string, TexturePtr> textures;
  void initTextures();

  std::shared_ptr<HUD> hud;

  std::shared_ptr<Storage> storage;

  // Player
  PlayerPtr player;
  std::string playerName;
  EnemyManagerPtr enemyManager;

  std::vector<BulletPtr> bullets;
  std::vector<ShieldPtr> shields;

  int level{};
  int points{};
  int highscore{};

  Game();
  ~Game(); // Prevent unwanted destruction

  void pollEvents();
  void update();
  void updateBullets();

  void restart(); // re/start new game
  void resetVariables();

  void handleScoreInput(); // user name input after game ends

  void render();

public:
  Game(Game &other) = delete;            // Prevent construction by copying
  void operator=(const Game &) = delete; // Prevent assignment

  void run(); // run application
  void quit();
  void gameOver();
  void nextLevel();

  static Game &getGame();
  PlayerPtr getPlayer() const;
  const GameState &getGameState() const;
  sf::RenderTarget &getRenderTarget() const;
  EnemyManagerPtr getEnemyManager() const;
  TexturePtr getTexture(std::string &name) const;
  std::vector<ShieldPtr> &getShields();
  const std::vector<BulletPtr> &getBullets() const;
  std::string getPlayerName() const;
  int getPoints() const;
  int getHighscore() const;
  int getLevel() const;

  void addPoints(int p);
  void pushBullet(BulletPtr bullet);
};

// utils
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);

#endif
