#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

const std::filesystem::path FILE_PATH =
    "C:/Users/kevro/Programming/Advent Of Code/AOC2023/Day 3 Gear "
    "Ratios/input.txt";

bool insideGrid(const std::vector<std::string>& grid,
                const std::pair<int, int>& coord) {
  int row = coord.first;
  int col = coord.second;
  const int totalRows = grid.size();
  const int totalCols = grid[0].size();

  if (0 <= row && row < totalRows && 0 <= col && col < totalCols) {
    return true;
  }

  return false;
}

int expandInteger(const std::vector<std::string>& grid,
                  const std::pair<int, int>& coord) {
  int row = coord.first;
  int col = coord.second;
  int xChange;

  std::string stringNumber = std::string(1, grid[row][col]);

  xChange = 1;
  while (insideGrid(grid, std::make_pair(row, col + xChange)) &&
         std::isdigit(grid[row][col + xChange])) {
    stringNumber += grid[row][col + xChange];

    xChange++;
  }

  if (row == 82 && col == 2) {
    int a = 1;
  }

  xChange = -1;
  while (insideGrid(grid, std::make_pair(row, col + xChange)) &&
         std::isdigit(grid[row][col + xChange])) {
    stringNumber = grid[row][col + xChange] + stringNumber;

    xChange--;
  }

  return std::stoi(stringNumber);
}

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

  const int ROWS = lines.size();
  const int COLS = lines[0].size();

  int total = 0;
  std::vector<std::pair<int, int>> directions = {
      {0, 1}, {1, 0},  {0, -1},  {-1, 0},   // directly adjacent directions,
      {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};  // and then diagonal directions
  std::string currentInteger = "";
  bool isPartNumber = false;

  for (int currRow = 0; currRow < ROWS; ++currRow) {
    for (int currCol = 0; currCol < COLS; ++currCol) {
      char currentCharacter = lines[currRow][currCol];
      if (currentCharacter == '*') {
        std::set<std::pair<int, int>> adjacentIntegerCoords;

        for (const auto& [xChange, yChange] : directions) {
          int newRow = currRow + yChange;
          int newCol = currCol + xChange;
          std::pair newCoord = {newRow, newCol};

          if (!insideGrid(lines, newCoord)) {
            continue;
          }

          char adjacentCharacter = lines[newRow][newCol];

          // If an integer is directly above or below the gear, there is no need
          // to check the diagonals in that row as the number will be expanded.
          if (newRow != currRow &&
              adjacentIntegerCoords.find(std::make_pair(newRow, currCol)) !=
                  adjacentIntegerCoords.end()) {
            continue;
          }

          if (std::isdigit(adjacentCharacter)) {
            adjacentIntegerCoords.insert(newCoord);
          }
        }

        if (adjacentIntegerCoords.size() == 2) {
          total +=
              expandInteger(lines, *adjacentIntegerCoords.begin()) *
              expandInteger(lines, *std::next(adjacentIntegerCoords.begin()));
        }
      }
    }
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}