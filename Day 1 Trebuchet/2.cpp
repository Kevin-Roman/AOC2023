#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

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

  std::vector<std::pair<std::string, std::string>> substitutions = {
      {"one", "o1e"},    // o required in the case of 'twone',
                         // e required in the case of 'oneight'
      {"two", "t2"},     // t required in the case of 'eightwo'
      {"three", "t3e"},  // t required in the case of 'eighthree',
                         // e required in the case of 'threeight'
      {"four", "4"},
      {"five", "5e"},  // e required in the case of 'fiveight'
      {"six", "6"},
      {"seven", "7n"},  // n required in the case of 'sevenine'
      {"eight", "e8"},  // e required in the case of 'nineight'
      {"nine", "9"},
  };

  while (input >> line) {
    const std::string pre = line;
    for (auto& [pattern, substitution] : substitutions) {
      size_t pos = 0;
      while ((pos = line.find(pattern, pos)) != std::string::npos) {
        line.replace(pos, pattern.length(), substitution);
        pos += substitution.length();
      }
    }

    char first_number = DEFAULT_CHAR;
    char last_number = DEFAULT_CHAR;

    for (auto currentChar : line) {
      if (std::isdigit(currentChar)) {
        if (first_number == DEFAULT_CHAR) {
          first_number = currentChar;
          last_number = currentChar;
        } else {
          last_number = currentChar;
        }
      }
    }

    if (first_number != DEFAULT_CHAR) {
      total += std::stoi(std::string(1, first_number) + last_number);
    }
  }

  input.close();

  std::cout << "Total: " << total << std::endl;

  return 0;
}
