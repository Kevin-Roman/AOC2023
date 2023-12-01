#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <regex>
#include <string>

int main() {
  const char DEFAULT_CHAR = '\0';
  std::filesystem::path filePath =
      "C:/Users/kevro/Programming/Advent Of Code/AOC2023/Day 1 "
      "Trebuchet/input.txt";
  std::ifstream input(filePath);
  std::string line;
  int total = 0;
  std::vector<std::pair<std::regex, std::string>> substitutions = {
      {std::regex("one"), "o1e"},    // o required in the case of 'twone',
                                     // e required in the case of 'oneight'
      {std::regex("two"), "t2"},     // t required in the case of 'eightwo'
      {std::regex("three"), "t3e"},  // t required in the case of 'eighthree',
                                     // e required in the case of 'threeight'
      {std::regex("four"), "4"},
      {std::regex("five"), "5e"},  // e required in the case of 'fiveight'
      {std::regex("six"), "6"},
      {std::regex("seven"), "7n"},  // n required in the case of 'sevenine'
      {std::regex("eight"), "e8"},  // e required in the case of 'nineight'
      {std::regex("nine"), "9"},
  };

  if (input.is_open()) {
    while (input >> line) {
      const std::string pre = line;
      for (const auto& [pattern, substitution] : substitutions) {
        line = std::regex_replace(line, pattern, substitution);
      }

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
      std::cout << pre << " " << line << " "
                << std::stoi(std::string(1, first_number) + last_number)
                << std::endl;
      total += std::stoi(std::string(1, first_number) + last_number);
    }

    input.close();
  } else {
    std::cerr << "Error opening file: " << filePath << std::endl;
    return 1;
  }

  std::cout << total << std::endl;

  return 0;
}