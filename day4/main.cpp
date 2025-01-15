#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

int isXmas(const std::vector<std::vector<char>> &matrix, const std::string &target, int row, int col, int rowChange,
           int colChange) {
    for (int i = 0; i < target.size(); i++) {
        int currRow = row + (rowChange * i);
        int currCol = col + (colChange * i);
        if (currRow < 0 || currRow >= matrix.size() || currCol < 0 || currCol >= matrix[0].size()) {
            // std::cout << "Out of bounds" << std::endl;
            return 0;
        }
        if (matrix[currRow][currCol] != target[i]) {
            // std::cout << "Wrong char | currChar:" << matrix[currRow][currCol] << " targetChar:" << target[i]
            //           << std::endl;
            return 0;
        }
    }
    return 1;
}

int isCrossMas(const std::vector<std::vector<char>> &matrix, int row, int col) {
    // bounds check
    if (row < 1 || row > matrix.size() - 2 || col < 1 || col > matrix[0].size() - 2) {
        return 0;
    }
    char curr = matrix[row][col];
    char upleft = matrix[row - 1][col - 1];
    char upright = matrix[row - 1][col + 1];
    char downleft = matrix[row + 1][col - 1];
    char downright = matrix[row + 1][col + 1];
    if (curr == 'A' && ((upleft == 'M' && downright == 'S') || (upleft == 'S' && downright == 'M')) &&
        ((upright == 'M' && downleft == 'S') || (upright == 'S' && downleft == 'M'))) {
        return 1;
    }
    return 0;
}

void part1(std::vector<std::vector<char>> matrix) {
    int numXmasFound = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            numXmasFound += isXmas(matrix, "XMAS", i, j, -1, 0);  // up
            numXmasFound += isXmas(matrix, "XMAS", i, j, 0, 1);   // right
            numXmasFound += isXmas(matrix, "XMAS", i, j, 1, 0);   // down
            numXmasFound += isXmas(matrix, "XMAS", i, j, 0, -1);  // left

            numXmasFound += isXmas(matrix, "XMAS", i, j, -1, -1);  // upleft
            numXmasFound += isXmas(matrix, "XMAS", i, j, -1, 1);   // upright
            numXmasFound += isXmas(matrix, "XMAS", i, j, 1, 1);    // downright
            numXmasFound += isXmas(matrix, "XMAS", i, j, 1, -1);   // downleft
        }
    }
    std::cout << "numFound = " << numXmasFound << std::endl;
}

void part2(std::vector<std::vector<char>> matrix) {
    int numCrossMasFound = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            numCrossMasFound += isCrossMas(matrix, i, j);
        }
    }
    std::cout << "numFound = " << numCrossMasFound << std::endl;
}

int main() {
    try {
        std::vector<std::vector<char>> matrix = readCharMatrix("input");
        part2(matrix);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
