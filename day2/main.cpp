#include "../util/InputUtil.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

bool isReportSafe(std::vector<int> &report) {
  bool isSafe = true;
  int d = report[1] - report[0];
  bool isIncreasing = d > 0;
  int sign;
  if (isIncreasing) {
    sign = 1;
  } else {
    sign = -1;
  }
  for (int i = 1; i < report.size(); i++) {
    int diff = report[i] - report[i - 1];
    diff *= sign;
    // std::cout << "comparing " << reports[i][j - 1] << " and " <<
    // reports[i][j]
    //           << " | diff= " << diff << std::endl;
    if (diff != 1 && diff != 2 && diff != 3) {
      isSafe = false;
      break;
    }
  }
  return isSafe;
}

void part1(std::vector<std::vector<int>> &reports) {
  int numSafeReports = 0;
  for (int i = 0; i < reports.size(); i++) {
    if (isReportSafe(reports[i])) {
      numSafeReports++;
    }
  }
  std::cout << "num safe reports: " << numSafeReports << std::endl;
}

void part2(std::vector<std::vector<int>> &reports) {
  int numSafeReports = 0;
  for (int i = 0; i < reports.size(); i++) {
    if (isReportSafe(reports[i])) {
      numSafeReports++;
    } else {
      std::vector<int> trimmedReport;
      for (int j = 0; j < reports[i].size(); j++) {
        trimmedReport.clear();
        for (int k = 0; k < reports[i].size(); k++) {
          if (k != j) {
            trimmedReport.push_back(reports[i][k]);
          }
        }
        if (isReportSafe(trimmedReport)) {
          numSafeReports++;
          break;
        }
      }
    }
  }
  std::cout << "num safe reports: " << numSafeReports << std::endl;
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
    part2(reports);

  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
