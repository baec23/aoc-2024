#include "InputUtil.h"
#include <fstream>
#include <stdexcept>
#include <string>

std::vector<std::string> readLines(const std::string &fileName) {
  std::ifstream file(fileName);
  if (!file) {
    throw std::runtime_error("Error: could not open file " + fileName);
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}
