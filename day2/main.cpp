#include "../util/InputUtil.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

void part1(std::vector<std::vector<int>> &reports) {
  int numSafeReports = 0;
  for (int i = 0; i < reports.size(); i++) {
    bool isSafe = true;
    int d = reports[i][1] - reports[i][0];
    bool isIncreasing = d > 0;
    int sign;
    if (isIncreasing) {
      sign = 1;
    } else {
      sign = -1;
    }
    for (int j = 1; j < reports[i].size(); j++) {
      int diff = reports[i][j] - reports[i][j - 1];
      diff *= sign;
      // std::cout << "comparing " << reports[i][j - 1] << " and " <<
      // reports[i][j]
      //           << " | diff= " << diff << std::endl;
      if (diff != 1 && diff != 2 && diff != 3) {
        isSafe = false;
        break;
      }
    }
    if (isSafe) {
      // std::cout << "SAFE" << std::endl << std::endl;
      numSafeReports++;
    } else {
      // std::cout << "UNSAFE" << std::endl << std::endl;
    }
  }
  std::cout << "num safe reports: " << numSafeReports << std::endl;
}

void part2(std::vector<std::vector<int>> &reports) {
  // for each report, try removing every level
}

int main() {
  try {
    std::vector<std::string> lines = readLines("input");
    std::vector<std::vector<int>> reports;
    for (const std::string &line : lines) {
      std::vector<int> levels;
      std::istringstream iss(line);
      int num;
      while (iss >> num) {
        levels.push_back(num);
      }
      reports.push_back(levels);
    }
    part1(reports);

  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
