#include "Game.h"
#include "HUD.h"

HUD::HUD()
{
    if (!font.loadFromFile("../resources/fonts/font.ttf"))
        throw std::runtime_error("Failed to load font");

    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    auto viewSize = Game::getGame().getRenderTarget().getView().getSize();

    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(Game::getGame().getPoints()));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(PADDING, PADDING);

    levelText.setFont(font);
    levelText.setString("Level: " + std::to_string(Game::getGame().getLevel() + 1));
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setOrigin(levelText.getGlobalBounds().width / 2.f, 0.f);
    levelText.setPosition(viewSize.x / 2, PADDING);

    highscoreText.setFont(font);
    // change to getHighscore and compare with current score
    highscoreText.setString("Highscore: " + std::to_string(Game::getGame().getPoints()));
    highscoreText.setCharacterSize(24);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setOrigin(highscoreText.getGlobalBounds().width, 0.f);
    highscoreText.setPosition(viewSize.x - PADDING, PADDING);

    // Start screen
    if (!logoImage.loadFromFile("../resources/fonts/logo.png"))
        throw std::runtime_error("Failed to load logo");

    logo.setTexture(logoImage);
    logo.setOrigin(logo.getGlobalBounds().width / 2.f, 0.f);
    logo.setScale(0.5f, 0.5f);
    logo.setPosition(viewSize.x / 2, 100.f);

    startTooltipText.setFont(font);
    startTooltipText.setString("[SPACE] Start\n\n[H] Leaderboard\n\n[ESC] Quit");
    startTooltipText.setCharacterSize(32);
    startTooltipText.setFillColor(sf::Color::White);
    startTooltipText.setOrigin(
        startTooltipText.getGlobalBounds().width / 2.f,
        0.f);
    startTooltipText.setPosition(viewSize.x / 2, viewSize.y / 2);

    // Pause screen
    pauseText.setFont(font);
    pauseText.setString("PAUSED");
    pauseText.setCharacterSize(64);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setOrigin(pauseText.getGlobalBounds().width / 2.f, 0.f);
    pauseText.setPosition(viewSize.x / 2, 100.f);

    pauseTooltipText.setFont(font);
    pauseTooltipText.setString("[SPACE] Continue\n\n[R] Restart\n\n[H] Leaderboard\n\n[ESC] Quit");
    pauseTooltipText.setCharacterSize(32);
    pauseTooltipText.setFillColor(sf::Color::White);
    pauseTooltipText.setOrigin(
        pauseTooltipText.getGlobalBounds().width / 2.f,
        0.f);
    pauseTooltipText.setPosition(viewSize.x / 2, viewSize.y / 2);

    // Game over screen
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2.f, 0.f);
    gameOverText.setPosition(viewSize.x / 2, 100.f);

    gameOverTooltipText.setFont(font);
    gameOverTooltipText.setString("[SPACE] Play again\n\n[H] Leaderboard\n\n[ESC] Quit");
    gameOverTooltipText.setCharacterSize(32);
    gameOverTooltipText.setFillColor(sf::Color::White);
    gameOverTooltipText.setOrigin(
        gameOverTooltipText.getGlobalBounds().width / 2.f,
        0.f);
    gameOverTooltipText.setPosition(viewSize.x / 2, viewSize.y / 2);

    gameOverNewHighscoreText.setFont(font);
    gameOverNewHighscoreText.setCharacterSize(32);
    gameOverNewHighscoreText.setFillColor(sf::Color::White);

    gameOverPointsText.setFont(font);
    gameOverPointsText.setCharacterSize(32);
    gameOverPointsText.setFillColor(sf::Color::White);

    // Name input screen
    nameInputText.setFont(font);
    nameInputText.setString("ENTER YOUR NAME");
    nameInputText.setCharacterSize(48);
    nameInputText.setFillColor(sf::Color::White);
    nameInputText.setOrigin(nameInputText.getGlobalBounds().width / 2.f, 0.f);
    nameInputText.setPosition(viewSize.x / 2, 196.f + 48.f + 96.f);

    nameInputNameLengthText.setFont(font);
    nameInputNameLengthText.setString("2 - 6 characters");
    nameInputNameLengthText.setCharacterSize(32);
    nameInputNameLengthText.setFillColor(sf::Color(255, 255, 255, 150));
    nameInputNameLengthText.setOrigin(nameInputNameLengthText.getGlobalBounds().width / 2.f, 0.f);
    nameInputNameLengthText.setPosition(viewSize.x / 2, 196.f + 48.f + 96.f + 64.f);

    nameInputPlayerName.setFont(font);
    nameInputPlayerName.setCharacterSize(64);
    nameInputPlayerName.setFillColor(sf::Color::White);

    nameInputTooltipText.setFont(font);
    nameInputTooltipText.setString("[ENTER] Save\t\t[ESC] Discard");
    nameInputTooltipText.setCharacterSize(32);
    nameInputTooltipText.setFillColor(sf::Color::White);
    nameInputTooltipText.setOrigin(
        nameInputTooltipText.getGlobalBounds().width / 2.f,
        0.f);
    nameInputTooltipText.setPosition(viewSize.x / 2, viewSize.y - 256.f);

    // Leaderboard screen
    leaderboardText.setFont(font);
    leaderboardText.setString("LEADERBOARD");
    leaderboardText.setCharacterSize(64);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setOrigin(leaderboardText.getGlobalBounds().width / 2.f, 0.f);
    leaderboardText.setPosition(viewSize.x / 2, PADDING);

    leaderboardTooltip.setFont(font);
    leaderboardTooltip.setString("[ESC] Back");
    leaderboardTooltip.setCharacterSize(32);
    leaderboardTooltip.setFillColor(sf::Color(255, 255, 255, 150));
    leaderboardTooltip.setOrigin(
        leaderboardTooltip.getGlobalBounds().width / 2.f,
        0.f);
    leaderboardTooltip.setPosition(viewSize.x / 2, 2 * PADDING + 64.f);
}

void HUD::update()
{
    auto &game = Game::getGame();
    auto viewSize = game.getRenderTarget().getView().getSize();
    overlay.setSize(viewSize);

    scoreText.setString("Score: " + std::to_string(game.getPoints()));

    levelText.setString("Level: " + std::to_string(game.getLevel() + 1));
    levelText.setOrigin(levelText.getGlobalBounds().width / 2.f, 0.f);
    levelText.setPosition(viewSize.x / 2, PADDING);

    // change to getHighscore and compare with current score
    highscoreText.setString("Highscore: " + std::to_string(game.getHighscore()));
    highscoreText.setOrigin(highscoreText.getGlobalBounds().width, 0.f);
    highscoreText.setPosition(viewSize.x - PADDING, PADDING);

    if (game.getGameState() == GameState::ScoreInput)
    {
        nameInputPlayerName.setString(game.getPlayerName());
        nameInputPlayerName.setOrigin(
            nameInputPlayerName.getGlobalBounds().width / 2.f,
            nameInputPlayerName.getGlobalBounds().height / 2.f);
        nameInputPlayerName.setPosition(viewSize.x / 2, viewSize.y / 2);
    }
}

void HUD::handleGameOver()
{
    auto &game = Game::getGame();
    auto viewSize = game.getRenderTarget().getView().getSize();

    int score = game.getPoints();
    gameOverPointsText.setString("Score: " + std::to_string(score));
    gameOverPointsText.setOrigin(
        gameOverPointsText.getGlobalBounds().width / 2.f,
        0.f);
    gameOverPointsText.setPosition(viewSize.x / 2, 196.f);

    int highscore = game.getHighscore();
    gameOverNewHighscoreText.setString(
        highscore > score
            ? std::to_string(highscore - score) + " more to set a new highscore"
            : "NEW HIGHSCORE!");
    gameOverNewHighscoreText.setOrigin(
        gameOverNewHighscoreText.getGlobalBounds().width / 2.f,
        0.f);
    gameOverNewHighscoreText.setPosition(viewSize.x / 2, 196.f + 48.f);
}

void HUD::setLeaderboard(std::vector<LeaderboardEntry> entries)
{
    auto viewSize = Game::getGame().getRenderTarget().getView().getSize();

    leaderboardEntries.clear();
    sf::Text baseText;
    baseText.setFont(font);
    baseText.setCharacterSize(28);
    baseText.setFillColor(sf::Color::White);

    int i = 0;
    for (const auto &entry : entries)
    {
        LeaderBoardEntryText entryText;

        entryText.score = sf::Text(baseText);
        entryText.score.setString(std::to_string(entry.score));
        entryText.score.setFillColor(sf::Color(0, 255, 255));
        entryText.score.setOrigin(entryText.score.getGlobalBounds().width, 0.f);
        entryText.score.setPosition(viewSize.x - 3 * PADDING, 164.f + i * 42);

        entryText.position = sf::Text(baseText);
        entryText.position.setString(std::to_string(i + 1) + ".");
        entryText.position.setFillColor(sf::Color(255, 0, 255, 150));
        entryText.position.setPosition(3 * PADDING, 164.f + i * 42);

        entryText.name = sf::Text(baseText);
        entryText.name.setString(entry.name);
        entryText.name.setPosition(3 * PADDING + 64.f, 164.f + i * 42);

        leaderboardEntries.push_back(entryText);
        ++i;
    }
}

void HUD::draw()
{
    auto &game = Game::getGame();
    auto &gameState = game.getGameState();
    sf::RenderTarget &target = game.getRenderTarget();

    switch (gameState)
    {

    case GameState::Running:
        target.draw(scoreText);
        target.draw(levelText);
        target.draw(highscoreText);
        break;
    case GameState::StartScreen:
        target.draw(overlay);
        target.draw(logo);
        target.draw(startTooltipText);
        break;
    case GameState::Paused:
        target.draw(overlay);
        target.draw(scoreText);
        target.draw(levelText);
        target.draw(highscoreText);
        target.draw(pauseText);
        target.draw(pauseTooltipText);
        break;
    case GameState::ScoreInput:
        target.draw(overlay);
        target.draw(scoreText);
        target.draw(levelText);
        target.draw(highscoreText);
        target.draw(gameOverText);
        target.draw(gameOverPointsText);
        target.draw(gameOverNewHighscoreText);
        target.draw(nameInputText);
        target.draw(nameInputNameLengthText);
        target.draw(nameInputPlayerName);
        target.draw(nameInputTooltipText);
        break;
    case GameState::GameOver:
        target.draw(overlay);
        target.draw(scoreText);
        target.draw(levelText);
        target.draw(highscoreText);
        target.draw(gameOverText);
        target.draw(gameOverTooltipText);
        target.draw(gameOverPointsText);
        target.draw(gameOverNewHighscoreText);
        break;
    case GameState::Leaderboard:
        target.draw(overlay);
        target.draw(leaderboardText);
        target.draw(leaderboardTooltip);
        for (const auto &entry : leaderboardEntries)
        {
            target.draw(entry.position);
            target.draw(entry.name);
            target.draw(entry.score);
        }
        break;
    }
}
