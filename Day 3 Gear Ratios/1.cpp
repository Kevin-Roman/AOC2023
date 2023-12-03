#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::filesystem::path FILE_PATH =
    "C:/Users/kevro/Programming/Advent Of Code/AOC2023/Day 3 Gear "
    "Ratios/input.txt";

int main() {
  std::ifstream file(FILE_PATH);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << FILE_PATH << std::endl;
    return 1;
  };

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  int ROWS = lines.size();
  int COLS = lines[0].size();

  int total = 0;
  std::vector<std::pair<int, int>> directions = {
      {0, 1}, {1, 0}, {1, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}};

  std::string currentInteger = "";
  bool isPartNumber = false;

  for (int r = 0; r < ROWS; ++r) {
    for (int c = 0; c < COLS; ++c) {
      char currentCharacter = lines[r][c];
      if (std::isdigit(currentCharacter)) {
        currentInteger += currentCharacter;

        for (const auto& [xChange, yChange] : directions) {
          int newR = r + yChange;
          int newC = c + xChange;
          bool outsideGrid =
              newR < 0 || newC < 0 || newR >= ROWS || newC >= COLS;
          if (outsideGrid) {
            continue;
          }

          char adjacentCharacter = lines[newR][newC];

          if (!std::isdigit(adjacentCharacter) && adjacentCharacter != '.') {
            isPartNumber = true;
          }
        }
      }

      if (!std::isdigit(currentCharacter) || c == COLS - 1) {
        if (isPartNumber) {
          total += std::stoi(currentInteger);
        }
        currentInteger = "";
        isPartNumber = false;
      }
    }
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}