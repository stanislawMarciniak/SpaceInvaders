#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <exception>

#include "Storage.h"

Storage::Storage() {}

std::vector<std::string> Storage::loadLevelLayout(int level)
{
  std::cout << "loading level layout...\n";

  level = level % 6; // there are currently 6 levels
  std::string filename = LEVELS_PATH + std::to_string(level) + ".txt";

  std::vector<std::string> rows;

  std::ifstream file(filename);

  if (file.is_open())
  {
    std::string line;

    // Read the file line by line
    while (std::getline(file, line))
    {
      // Add each line to the vector
      rows.push_back(line);
    }

    // Close the file
    file.close();

    return rows;
  }
  else
  {
    throw std::runtime_error("Error opening file " + filename);
  }

  return rows;
}

std::vector<LeaderboardEntry> Storage::loadLeaderboard()
{
  std::cout << "loading leaderboard...\n";

  std::vector<LeaderboardEntry> entries;

  std::ifstream file(LEADERBOARD_FILE);

  if (!file.good())
  {
    std::cout << "Failed to open leaderboard file. Creating a new one..." << std::endl;
    std::filesystem::create_directories("../storage");
    std::ofstream outFile(LEADERBOARD_FILE);
    outFile.close();

    file.open(LEADERBOARD_FILE);
  }

  if (file.is_open())
  {
    std::string line;
    // Read the file line by line
    while (std::getline(file, line))
    {
      if (line == "")
        continue;

      LeaderboardEntry newEntry;

      std::stringstream lineStream(line);
      std::string column;
      int columnNumber = 0;
      // split the line into words
      while (getline(lineStream, column, ' '))
      {
        switch (columnNumber)
        {
        case 0:
          newEntry.name = column;
          break;
        case 1:
          if (column != "0" && atoi(column.c_str()) == 0)
          {
            file.close();
            throw std::runtime_error("Failed to parse leaderboard entry score: " + line);
          }

          newEntry.score = atoi(column.c_str());
          break;
        }
        columnNumber++;
      }

      entries.push_back(newEntry);
    }
  }
  else
    throw std::runtime_error("Failed to open leaderboard file");

  // should be sorted before saving, but just making sure
  std::sort(entries.begin(), entries.end(), [](const LeaderboardEntry &a, const LeaderboardEntry &b)
            { return a.score > b.score; });

  file.close();

  return entries;
}

void Storage::saveScore(int score, std::string &name)
{

  std::cout << "saving score: " << name << " " << score << std::endl;

  auto leaderboard = loadLeaderboard();

  leaderboard.push_back(LeaderboardEntry{score, name});

  std::fstream file(LEADERBOARD_FILE, std::fstream::out | std::fstream::trunc);

  if (file.is_open())
  {
    // should be sorted before saving, but just making sure
    std::sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardEntry &a, const LeaderboardEntry &b)
              { return a.score > b.score; });

    // save 20 best scores
    for (auto it = leaderboard.begin(); it < leaderboard.begin() + 20; ++it)
      file << it->name << " " << it->score << std::endl;
  }
  else
    throw std::runtime_error("Failed to open leadboard file");

  file.close();
}
