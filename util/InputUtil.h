#ifndef INPUT_UTIL_H
#define INPUT_UTIL_H

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> readLines(const std::string &fileName);
std::vector<std::vector<char>> readCharMatrix(const std::string &fileName);
std::vector<std::vector<int>> readIntMatrix(const std::string &fileName);
std::vector<std::string> splitStr(const std::string &str, const std::string &delimiter);

template <typename T>
void printVec(const std::vector<T> &vec, bool isOneLine = true) {
    if (isOneLine) {
        std::cout << "[";
        for (int i = 0; i < vec.size(); i++) {
            std::cout << vec[i];
            if (i < vec.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
        return;
    }

    for (const auto &item : vec) {
        std::cout << item << std::endl;
    }
}

#endif
