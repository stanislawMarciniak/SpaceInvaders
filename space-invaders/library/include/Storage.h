#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>

const std::string LEVELS_PATH = "../resources/levels/";
const std::string LEADERBOARD_FILE = "../storage/leaderboard.txt";

struct LeaderboardEntry
{
  int score;
  std::string name;
};

class Storage
{
public:
  Storage();
  virtual ~Storage() = default;

  std::vector<std::string> loadLevelLayout(int level);
  std::vector<LeaderboardEntry> loadLeaderboard();
  void saveScore(int score, std::string &name);
};

#endif
