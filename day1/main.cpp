#include "../util/InputUtil.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

void part1(std::vector<int> &leftNums, std::vector<int> &rightNums) {
  std::sort(leftNums.begin(), leftNums.end());
  std::sort(rightNums.begin(), rightNums.end());

  int totalDiff = 0;
  for (int i = 0; i < leftNums.size(); i++) {
    int diff = std::abs(leftNums[i] - rightNums[i]);
    totalDiff += diff;
  }
  std::cout << "total diff: " << totalDiff << std::endl;
}

void part2(std::vector<int> &leftNums, std::vector<int> &rightNums) {
  std::map<int, int> rightFreqMap;
  // Create right freq map
  for (int i = 0; i < rightNums.size(); i++) {
    if (rightFreqMap.find(rightNums[i]) == rightFreqMap.end()) {
      rightFreqMap[rightNums[i]] = 0;
    }
    rightFreqMap[rightNums[i]] = rightFreqMap[rightNums[i]] + 1;
  }

  // iterate left and get similarity score
  long toReturn = 0;
  for (int i = 0; i < leftNums.size(); i++) {
    if (rightFreqMap.find(leftNums[i]) != rightFreqMap.end()) {
      toReturn += leftNums[i] * rightFreqMap[leftNums[i]];
    }
  }
  std::cout << "total sim score: " << toReturn << std::endl;
}

int main() {
  try {
    std::vector<std::string> lines = readLines("input");
    std::vector<int> leftNums;
    std::vector<int> rightNums;
    for (const std::string &line : lines) {
      int leftNum, rightNum;
      std::istringstream iss(line);
      iss >> leftNum >> rightNum;
      leftNums.push_back(leftNum);
      rightNums.push_back(rightNum);
    }

    part2(leftNums, rightNums);

  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
