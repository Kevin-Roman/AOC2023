#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

int main() {
  const char DEFAULT_CHAR = '\0';
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
  bool valid = true;

  while (input >> word) {
    if (word == "Game") {
      if (valid) {
        total += id;
      }

      input >> word;
      word.pop_back();
      id = std::stoi(word);
      valid = true;
    } else {
      int count = std::stoi(word);
      input >> word;
      std::string colour = word.substr(0, word.find_first_of(";,"));

      if (colour == "red" && count > 12) {
        valid = false;
      } else if (colour == "green" && count > 13) {
        valid = false;
      } else if (colour == "blue" && count > 14) {
        valid = false;
      }
    }
  }

  if (valid) {
    total += id;
  }

  input.close();

  std::cout << total << std::endl;

  return 0;
}