#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Storage.h"

constexpr float PADDING = 20.f;

struct LeaderBoardEntryText
{
  sf::Text position;
  sf::Text score;
  sf::Text name;
};

class HUD
{
private:
  sf::Font font;
  sf::RectangleShape overlay;

  // Score and Level display
  sf::Text scoreText;
  sf::Text highscoreText;
  sf::Text levelText;

  // Start screen
  sf::Sprite logo;
  sf::Texture logoImage;
  sf::Text startTooltipText;

  // Name input screen
  sf::Text nameInputText;
  sf::Text nameInputNameLengthText;
  sf::Text nameInputPlayerName;
  sf::Text nameInputTooltipText;

  // Game over screen
  sf::Text gameOverText;
  sf::Text gameOverPointsText;
  sf::Text gameOverNewHighscoreText;
  sf::Text gameOverTooltipText;

  // Pause screen
  sf::Text pauseText;
  sf::Text pauseTooltipText;

  // Pause screen
  sf::Text leaderboardText;
  sf::Text leaderboardTooltip;
  std::vector<LeaderBoardEntryText> leaderboardEntries;

  sf::Sprite background;

public:
  HUD();
  ~HUD() = default;

  void draw();
  void update();

  void handleGameOver();
  void setLeaderboard(std::vector<LeaderboardEntry>);
};

#endif
