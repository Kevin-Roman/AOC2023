#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

constexpr char DEFAULT_CHAR = '\0';
constexpr int RED_THRESHOLD = 12;
constexpr int GREEN_THRESHOLD = 13;
constexpr int BLUE_THRESHOLD = 14;

bool isValidColor(const std::string& color, int count) {
  return (color == "red" && count > RED_THRESHOLD) ||
         (color == "green" && count > GREEN_THRESHOLD) ||
         (color == "blue" && count > BLUE_THRESHOLD);
}

int main() {
  const std::filesystem::path filePath =
      "C:/Users/kevro/Programming/Advent Of Code/AOC2023/Day 2 Cube "
      "Conundrum/input.txt";
  std::ifstream input(filePath);

  if (!input.is_open()) {
    std::cerr << "Error opening file: " << filePath << std::endl;
    return 1;
  }

  std::string word;
  int total = 0;
  int id = 0;
  bool isGameValid = true;

  while (input >> word) {
    if (word == "Game") {
      if (isGameValid) {
        total += id;
      }

      input >> word;
      word.pop_back();
      id = std::stoi(word);
      isGameValid = true;
    } else {
      int count = std::stoi(word);
      input >> word;
      const std::string colour = word.substr(0, word.find_first_of(";,"));

      if (isValidColor(colour, count)) {
        isGameValid = false;
      }
    }
  }

  if (input.eof() && isGameValid) {
    total += id;
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}