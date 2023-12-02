#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

int main() {
  const char DEFAULT_CHAR = '\0';
  const std::filesystem::path filePath =
      "C:/Users/kevro/Programming/Advent Of Code/AOC2023/Day 1 "
      "Trebuchet/input.txt";
  std::ifstream input(filePath);

  if (!input.is_open()) {
    std::cerr << "Error opening file: " << filePath << std::endl;
    return 1;
  }

  std::string line;
  int total = 0;

  while (input >> line) {
    char first_number = DEFAULT_CHAR;
    char last_number = DEFAULT_CHAR;

    for (auto& character : line) {
      if (std::isdigit(character)) {
        if (first_number == DEFAULT_CHAR) {
          first_number = character;
          last_number = character;
        } else {
          last_number = character;
        }
      }
    }

    total += std::stoi(std::string(1, first_number) + last_number);
  }

  input.close();

  std::cout << total << std::endl;

  return 0;
}