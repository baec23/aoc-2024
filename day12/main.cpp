#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

void traverse(const vector<vector<char>> &grid, Point curr, const Point &prev, std::set<Point> *visited, int *area,
              int *perimeter) {
    if (curr.row < 0 || curr.row >= grid.size() || curr.col < 0 || curr.col >= grid[0].size()) {
        *perimeter += 1;
        return;
    }
    if (prev.row != -1 && prev.col != -1) {
        char currType = grid[curr.row][curr.col];
        char prevType = grid[prev.row][prev.col];
        if (currType != prevType) {
            *perimeter += 1;
            return;
        }
        if (visited->find(curr) != visited->end()) {
            return;
        }
    }
    *area += 1;
    visited->insert(curr);
    traverse(grid, curr.up(), curr, visited, area, perimeter);
    traverse(grid, curr.right(), curr, visited, area, perimeter);
    traverse(grid, curr.down(), curr, visited, area, perimeter);
    traverse(grid, curr.left(), curr, visited, area, perimeter);
}

void traverse2(const vector<vector<char>> &grid, Point curr, const Point &prev, std::set<Point> *visited, int *area,
               int *numCorners) {
    if (curr.row < 0 || curr.row >= grid.size() || curr.col < 0 || curr.col >= grid[0].size()) {
        return;
    }
    char currType = grid[curr.row][curr.col];
    if (prev.row != -1 && prev.col != -1) {
        char prevType = grid[prev.row][prev.col];
        if (currType != prevType) {
            return;
        }
        if (visited->find(curr) != visited->end()) {
            return;
        }
    }
    *area += 1;
    // if up/down are equal or left/right are equal
    Point up = curr.up();
    Point right = curr.right();
    Point down = curr.down();
    Point left = curr.left();
    Point ur = {up.row, right.col};
    Point dr = {down.row, right.col};
    Point dl = {down.row, left.col};
    Point ul = {up.row, left.col};
    char upType, rightType, downType, leftType, urType, drType, dlType, ulType;
    if (up.row < 0 || up.row >= grid.size() || up.col < 0 || up.col >= grid[0].size()) {
        upType = '?';
    } else {
        upType = grid[up.row][up.col];
    }
    if (right.row < 0 || right.row >= grid.size() || right.col < 0 || right.col >= grid[0].size()) {
        rightType = '?';
    } else {
        rightType = grid[right.row][right.col];
    }
    if (down.row < 0 || down.row >= grid.size() || down.col < 0 || down.col >= grid[0].size()) {
        downType = '?';
    } else {
        downType = grid[down.row][down.col];
    }
    if (left.row < 0 || left.row >= grid.size() || left.col < 0 || left.col >= grid[0].size()) {
        leftType = '?';
    } else {
        leftType = grid[left.row][left.col];
    }

    if (ur.row < 0 || ur.row >= grid.size() || ur.col < 0 || ur.col >= grid[0].size()) {
        urType = '?';
    } else {
        urType = grid[ur.row][ur.col];
    }
    if (dr.row < 0 || dr.row >= grid.size() || dr.col < 0 || dr.col >= grid[0].size()) {
        drType = '?';
    } else {
        drType = grid[dr.row][dr.col];
    }
    if (dl.row < 0 || dl.row >= grid.size() || dl.col < 0 || dl.col >= grid[0].size()) {
        dlType = '?';
    } else {
        dlType = grid[dl.row][dl.col];
    }
    if (ul.row < 0 || ul.row >= grid.size() || ul.col < 0 || ul.col >= grid[0].size()) {
        ulType = '?';
    } else {
        ulType = grid[ul.row][ul.col];
    }

    if (currType == urType && currType != upType && currType != rightType) {
        cout << "(" << curr.row << ", " << curr.col << ") " << currType << " | ur Corner found" << endl;
        *numCorners += 1;
    }
    if (currType != urType &&
        ((currType == upType && currType == rightType) || (currType != upType && currType != rightType))) {
        cout << "(" << curr.row << ", " << curr.col << ") " << currType << " | ur Corner found" << endl;
        *numCorners += 1;
    }

    if (currType == drType && currType != downType && currType != rightType) {
        cout << "(" << curr.row << ", " << curr.col << ") " << currType << " | ur Corner found" << endl;
        *numCorners += 1;
    }
    if (currType != drType &&
        ((currType == downType && currType == rightType) || (currType != downType && currType != rightType))) {
        cout << "(" << curr.row << ", " << curr.col << ") " << currType << " | dr Corner found" << endl;
        *numCorners += 1;
    }

    if (currType == dlType && currType != downType && currType != leftType) {
        cout << "(" << curr.row << ", " << curr.col << ") " << currType << " | ur Corner found" << endl;
        *numCorners += 1;
    }
    if (currType != dlType &&
        ((currType == downType && currType == leftType) || (currType != downType && currType != leftType))) {
        cout << "(" << curr.row << ", " << curr.col << ") " << currType << " | dl Corner found" << endl;
        *numCorners += 1;
    }

    if (currType == ulType && currType != upType && currType != leftType) {
        cout << "(" << curr.row << ", " << curr.col << ") " << currType << " | ur Corner found" << endl;
        *numCorners += 1;
    }
    if (currType != ulType &&
        ((currType == upType && currType == leftType) || (currType != upType && currType != leftType))) {
        cout << "(" << curr.row << ", " << curr.col << ") " << currType << " | ul Corner found" << endl;
        *numCorners += 1;
    }

    visited->insert(curr);
    traverse2(grid, curr.up(), curr, visited, area, numCorners);
    traverse2(grid, curr.right(), curr, visited, area, numCorners);
    traverse2(grid, curr.down(), curr, visited, area, numCorners);
    traverse2(grid, curr.left(), curr, visited, area, numCorners);
}

void part1(const vector<vector<char>> &grid) {
    std::set<Point> visited;
    long total = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            Point curr = {i, j};
            Point prev = {-1, -1};
            if (visited.find(curr) == visited.end()) {
                int perimeter = 0;
                int area = 0;
                traverse(grid, curr, prev, &visited, &area, &perimeter);
                long regionTotal = perimeter * area;
                total += regionTotal;
                cout << "Starting at (" << curr.row << ", " << curr.col << ") | "
                     << "After traversing... perimeter = " << perimeter << " | area = " << area
                     << " | regionTotal = " << regionTotal << endl;
            }
        }
    }
    cout << endl << "Total = " << total << endl;
}

void part2(const vector<vector<char>> &grid) {
    std::set<Point> visited;
    long total = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            Point curr = {i, j};
            Point prev = {-1, -1};
            if (visited.find(curr) == visited.end()) {
                int numCorners = 0;
                int area = 0;
                traverse2(grid, curr, prev, &visited, &area, &numCorners);
                long regionTotal = numCorners * area;
                total += regionTotal;
                cout << "Starting at (" << curr.row << ", " << curr.col << ") | "
                     << "After traversing... numCorners = " << numCorners << " | area = " << area
                     << " | regionTotal = " << regionTotal << endl;
            }
        }
    }
    cout << endl << "Total = " << total << endl;
}

int main() {
    try {
        vector<vector<char>> matrix = readCharMatrix("input");
        part2(matrix);

    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
