#include <fstream>
#include <iostream>
#include <locale>
#include <string>

int main() {
  const char UNINITIALISED = '\0';
  std::ifstream input(
      "C:\\Users\\kevro\\Programming\\Advent Of Code\\AOC2023\\Day 1 "
      "Trebuchet\\input.txt");
  std::string line;
  int total = 0;

  if (input.is_open()) {
    while (input >> line) {
      char first_number = UNINITIALISED;
      char last_number = UNINITIALISED;

      for (char& character : line) {
        if (std::isdigit(character)) {
          if (first_number == UNINITIALISED) {
            first_number = character;
            last_number = character;
          } else {
            last_number = character;
          }
        }
      }

      total += std::stoi(std::string(1, first_number) + last_number);
    }
  }
  std::cout << total << std::endl;
}