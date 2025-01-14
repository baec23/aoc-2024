#include "../util/InputUtil.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

void part1(std::vector<std::vector<int>> &reports) {}

void part2(std::vector<std::vector<int>> &reports) {}

int main() {
  try {
    std::vector<std::string> lines = readLines("input");
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
