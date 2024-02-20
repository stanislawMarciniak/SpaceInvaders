#include <exception>

#include "Game.h"

constexpr int DEFAULT_VIEW_WIDTH = 768.f;
constexpr int DEFAULT_VIEW_HEIGHT = 1024.f;

// Contructor
Game::Game()
{
  initWindow();
  initTextures();
}

Game &Game::getGame()
{
  static Game game;
  return game;
}

const GameState &Game::getGameState() const
{
  return gameState;
}

// Destructor
Game::~Game()
{
}

void Game::initWindow()
{
  auto desktop = sf::VideoMode::getDesktopMode();

  // developed on a 2880x1800 screen
  videoMode.height = DEFAULT_VIEW_HEIGHT * (static_cast<float>(desktop.width) / 2880.f);
  videoMode.width = DEFAULT_VIEW_WIDTH * (static_cast<float>(desktop.height) / 1800.f);

  window = std::make_shared<sf::RenderWindow>(videoMode, "Space Invaders");
  window->setFramerateLimit(30);
  window->setPosition(sf::Vector2i(desktop.width / 2 - window->getSize().x / 2, desktop.height / 2 - window->getSize().y / 2));

  view.setSize(DEFAULT_VIEW_WIDTH, DEFAULT_VIEW_HEIGHT);
  view.setCenter(view.getSize().x / 2.f, view.getSize().y / 2.f);

  window->setView(view);
}

sf::RenderTarget &Game::getRenderTarget() const
{
  return *window;
}

EnemyManagerPtr Game::getEnemyManager() const
{
  return enemyManager;
}

void Game::initTextures()
{
  try
  {
    textures["player"] = std::make_shared<sf::Texture>();
    if (!textures["player"]->loadFromFile("../resources/textures/player.png"))
      throw "player";

    textures["playerBullet"] = std::make_shared<sf::Texture>();
    if (!textures["playerBullet"]->loadFromFile("../resources/textures/playerBullet.png"))
      throw "playerBullet";

    textures["enemyBullet"] = std::make_shared<sf::Texture>();
    if (!textures["enemyBullet"]->loadFromFile("../resources/textures/enemyBullet.png"))
      throw "enemyBullet";

    textures["crab"] = std::make_shared<sf::Texture>();
    if (!textures["crab"]->loadFromFile("../resources/textures/crab.png"))
      throw "crab";

    textures["octopus"] = std::make_shared<sf::Texture>();
    if (!textures["octopus"]->loadFromFile("../resources/textures/octopus.png"))
      throw "octopus";

    textures["squid"] = std::make_shared<sf::Texture>();
    if (!textures["squid"]->loadFromFile("../resources/textures/squid.png"))
      throw "squid";

    textures["ufo"] = std::make_shared<sf::Texture>();
    if (!textures["ufo"]->loadFromFile("../resources/textures/ufo.png"))
      throw "ufo";

    textures["shield"] = std::make_shared<sf::Texture>();
    if (!textures["shield"]->loadFromFile("../resources/textures/shield.png"))
      throw "shield";
  }
  catch (std::string e)
  {
    std::cout << "Failed to load " << e << " texture.\n";
    quit();
  }
}

TexturePtr Game::getTexture(std::string &name) const
{
  return textures.at(name);
}

void Game::addPoints(int p)
{
  points += p;
}

void Game::pushBullet(BulletPtr bullet)
{
  bullets.push_back(bullet);
}

const std::vector<BulletPtr> &Game::getBullets() const
{
  return bullets;
}

std::string Game::getPlayerName() const
{
  return playerName;
}

void Game::run()
{
  try
  {
    std::cout << "running game...\n";

    hud = std::make_shared<HUD>();
    storage = std::make_shared<Storage>();
    enemyManager = std::make_shared<EnemyManager>();

    while (window->isOpen())
    {
      this->update();

      this->render();
    }
  }
  catch (std::runtime_error e)
  {
    std::cout << "Error running game\n"
              << e.what() << std::endl;
    quit();
  }
}

void Game::quit()
{
  window->close();
}

void Game::gameOver()
{
  // User inputs their name after the game finishes
  playerName = "";
  hud->handleGameOver();
  gameState = GameState::ScoreInput;
}

void Game::restart()
{
  std::cout << "starting new game...\n";
  resetVariables();
  gameState = GameState::Running;
}

void Game::resetVariables()
{
  try
  {
    points = 0;
    level = 0;
    playerName = "";
    bullets.clear();

    auto viewSize = getRenderTarget().getView().getSize();

    player = std::make_shared<Player>(sf::Vector2f(
        viewSize.x / 2.f,
        viewSize.y - 50.f));

    // spawn shields
    // use temporary shield to get it's width and place shields with equal spacing
    auto tempShield = std::make_shared<Shield>(sf::Vector2f(0.f, 0.f));
    float shieldWidth = tempShield->getBounds().width;
    int const distanceBetweenShilds = (viewSize.x - 4 * shieldWidth) / 5;

    shields.clear();
    for (int i = 0; i < 4; ++i)
    {
      float shieldX = (distanceBetweenShilds + shieldWidth) * (i + 1) - shieldWidth / 2;
      float shieldY = viewSize.y - 150.f;
      auto shield = std::make_shared<Shield>(sf::Vector2f(shieldX, shieldY));
      shields.push_back(shield);
    }

    // load first level
    auto levelLayout = storage->loadLevelLayout(level);
    enemyManager->loadWave(levelLayout);

    auto leaderboard = storage->loadLeaderboard();
    if (leaderboard.size())
      highscore = leaderboard.at(0).score;
  }
  catch (std::runtime_error e)
  {
    std::cout << "Error resetting variables\n"
              << e.what() << std::endl;
    quit();
  }
}

void Game::pollEvents()
{
  while (window->pollEvent(ev))
  {
    switch (ev.type)
    {
    case sf::Event::Closed:
      quit();
      break;
    case sf::Event::Resized:
      view = getLetterboxView(view, ev.size.width, ev.size.height);
      break;
    case sf::Event::KeyPressed:
      if (gameState == GameState::ScoreInput)
        handleScoreInput();
      else
        switch (ev.key.code)
        {
        case sf::Keyboard::G:
          gameOver();
          break;
        case sf::Keyboard::Escape:
          if (gameState == GameState::Running)
            gameState = GameState::Paused;
          else if (gameState == GameState::Leaderboard)
            gameState = prevGameState;
          else if (gameState == GameState::ScoreInput)
            gameState = GameState::GameOver;
          else
            quit();
          break;
        case sf::Keyboard::Space:
          if (gameState == GameState::Paused)
            gameState = GameState::Running;
          else if (gameState == GameState::StartScreen || gameState == GameState::GameOver)
            restart();
          break;
        case sf::Keyboard::R:
          if (gameState == GameState::Paused)
            restart();
          break;
        case sf::Keyboard::H:
          if (gameState != GameState::Running && gameState != GameState::Leaderboard)
          {
            prevGameState = gameState;
            hud->setLeaderboard(storage->loadLeaderboard());
            gameState = GameState::Leaderboard;
          }
          break;
        }
      break;
    }
  }
}

void Game::handleScoreInput()
{
  if (gameState != GameState::ScoreInput)
    return;

  switch (ev.key.code)
  {
  case sf::Keyboard::Escape:
    // discard the score
    gameState = GameState::GameOver;
    break;
  case sf::Keyboard::Enter:
    if (playerName.length() > 1)
    {
      storage->saveScore(points, playerName);
      hud->setLeaderboard(storage->loadLeaderboard());
      gameState = GameState::GameOver;
    }
    break;
  case sf::Keyboard::Backspace:
    if (playerName.length())
      playerName.pop_back();
    break;
  default:
    if (playerName.length() < 6 && ev.text.unicode >= 0 && ev.text.unicode < 26) // from a to z
      playerName += static_cast<char>(ev.text.unicode + 65);
  }
}

void Game::update()
{
  pollEvents();

  hud->update();

  if (gameState != GameState::Running)
    return;

  updateBullets();

  if (player->isDead())
  {
    gameOver();
    return;
  }

  player->update();

  enemyManager->update();
}

void Game::updateBullets()
{
  for (auto it = bullets.begin(); it != bullets.end();)
  {
    auto bullet = *it;
    bullet->update();
    if (bullet->isDead())
    {
      bullets.erase(it);
      continue;
    }

    ++it;
  }
}

void Game::nextLevel()
{
  try
  {

    auto levelLayout = storage->loadLevelLayout(++level);
    enemyManager->loadWave(levelLayout);
    std::cout << "Level " << level << std::endl;
  }
  catch (std::runtime_error e)
  {
    std::cout << "Error loading next level;\n"
              << e.what() << std::endl;
    quit();
  }
}

void Game::render()
{
  window->setView(view);

  window->clear();

  if (player)
    player->draw();

  enemyManager->draw();
  for (const auto &b : bullets)
  {
    b->draw();
  }
  for (const auto &shield : shields)
  {
    shield->draw();
  }

  hud->draw();

  window->display();
}

/*
  UTILS
*/

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{

  // Compares the aspect ratio of the window to the aspect ratio of the view,
  // and sets the view's viewport accordingly in order to archieve a letterbox effect.
  // A new view (with a new viewport set) is returned.

  float windowRatio = windowWidth / (float)windowHeight;
  float viewRatio = view.getSize().x / (float)view.getSize().y;
  float sizeX = 1;
  float sizeY = 1;
  float posX = 0;
  float posY = 0;

  bool horizontalSpacing = true;
  if (windowRatio < viewRatio)
    horizontalSpacing = false;

  // If horizontalSpacing is true, the black bars will appear on the left and right side.
  // Otherwise, the black bars will appear on the top and bottom.

  if (horizontalSpacing)
  {
    sizeX = viewRatio / windowRatio;
    posX = (1 - sizeX) / 2.f;
  }

  else
  {
    sizeY = windowRatio / viewRatio;
    posY = (1 - sizeY) / 2.f;
  }

  view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

  return view;
}

std::vector<ShieldPtr> &Game::getShields()
{
  return shields;
}

PlayerPtr Game::getPlayer() const
{
  return player;
}

int Game::getPoints() const
{
  return points;
}

int Game::getHighscore() const
{
  return points > highscore ? points : highscore;
}

int Game::getLevel() const
{
  return level;
}