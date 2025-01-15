#include "InputUtil.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::vector<std::string> readLines(const std::string& fileName) {
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

std::vector<std::vector<char>> readCharMatrix(const std::string& fileName) {
    std::vector<std::vector<char>> toReturn;
    std::vector<std::string> lines = readLines(fileName);
    for (int i = 0; i < lines.size(); i++) {
        std::vector<char> toPush;
        for (int j = 0; j < lines[i].size(); j++) {
            toPush.push_back(lines[i][j]);
        }
        toReturn.push_back(toPush);
    }
    return toReturn;
}

std::vector<std::string> splitStr(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = 0;

    // Iterate through the string and find the delimiter
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();  // Move past the delimiter
    }

    // Add the last token
    tokens.push_back(str.substr(start));
    return tokens;
}
