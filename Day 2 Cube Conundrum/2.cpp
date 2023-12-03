#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <locale>
#include <string>

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

  int maxRed = 0;
  int maxGreen = 0;
  int maxBlue = 0;

  while (input >> word) {
    if (word == "Game") {
      total += maxRed * maxGreen * maxBlue;

      input >> word;
      word.pop_back();
      id = std::stoi(word);
      maxRed = 0;
      maxGreen = 0;
      maxBlue = 0;
    } else {
      int count = std::stoi(word);
      input >> word;
      const std::string colour = word.substr(0, word.find_first_of(";,"));

      if (colour == "red") {
        maxRed = std::max(maxRed, count);
      } else if (colour == "green") {
        maxGreen = std::max(maxGreen, count);
      } else if (colour == "blue") {
        maxBlue = std::max(maxBlue, count);
      }
    }
  }

  if (input.eof()) {
    total += maxRed * maxGreen * maxBlue;
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}