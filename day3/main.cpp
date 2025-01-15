#include "../util/InputUtil.h"
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

void part1(std::vector<std::string> instructions) {
  std::regex num1Pattern(R"(\(\d+,)");
  std::regex num2Pattern(R"(,\d+\))");
  long toReturn = 0;
  for (int i = 0; i < instructions.size(); i++) {
    if (instructions[i][0] == 'd') {
      continue;
    }
    int num1, num2;
    std::smatch match;
    if (std::regex_search(instructions[i], match, num1Pattern)) {
      std::string matchStr = match.str();
      num1 = std::stoi(matchStr.substr(1, matchStr.size() - 2));
    }
    if (std::regex_search(instructions[i], match, num2Pattern)) {
      std::string matchStr = match.str();
      num2 = std::stoi(matchStr.substr(1, matchStr.size() - 2));
    }
    // std::cout << "Multiplied " << num1 << " and " << num2 << std::endl;
    long product = num1 * num2;
    toReturn += product;
  }
  std::cout << "Total = " << toReturn << std::endl;
}

void part2(std::vector<std::string> instructions) {
  std::regex num1Pattern(R"(\(\d+,)");
  std::regex num2Pattern(R"(,\d+\))");
  long toReturn = 0;
  bool isEnabled = true;
  for (int i = 0; i < instructions.size(); i++) {
    std::cout << "Current instruction: " << instructions[i] << std::endl;
    if (instructions[i] == "do()") {
      isEnabled = true;
      continue;
    }
    if (instructions[i] == "don't()") {
      isEnabled = false;
      continue;
    }
    if (!isEnabled) {
      continue;
    }

    int num1, num2;
    std::smatch match;
    if (std::regex_search(instructions[i], match, num1Pattern)) {
      std::string matchStr = match.str();
      num1 = std::stoi(matchStr.substr(1, matchStr.size() - 2));
    }
    if (std::regex_search(instructions[i], match, num2Pattern)) {
      std::string matchStr = match.str();
      num2 = std::stoi(matchStr.substr(1, matchStr.size() - 2));
    }
    // std::cout << "Multiplied " << num1 << " and " << num2 << std::endl;
    long product = num1 * num2;
    toReturn += product;
  }
  std::cout << "Total = " << toReturn << std::endl;
}

int main() {
  try {
    std::vector<std::string> lines = readLines("input");
    std::vector<std::string> instructions;
    std::regex pattern(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");

    for (int i = 0; i < lines.size(); i++) {
      auto matchesBegin =
          std::sregex_iterator(lines[i].begin(), lines[i].end(), pattern);
      auto matchesEnd = std::sregex_iterator();
      for (auto it = matchesBegin; it != matchesEnd; it++) {
        std::smatch match = *it;
        instructions.push_back(match.str());
      }
    }

    part2(instructions);
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
