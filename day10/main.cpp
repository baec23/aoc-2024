#include <cstdlib>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

struct Point {
    int row;
    int col;

    bool operator<(const Point &other) const { return (row < other.row) || (row == other.row && col < other.col); }
    bool operator==(const Point &other) const { return (row == other.row) && (col == other.col); }

    Point up() { return {row - 1, col}; }
    Point right() { return {row, col + 1}; }
    Point down() { return {row + 1, col}; }
    Point left() { return {row, col - 1}; }
};

bool isValidTrailHelper(const vector<vector<int>> &grid, Point curr, Point end, int prevValue,
                        std::set<Point> *visited) {
    if (curr.row < 0 || curr.row >= grid.size() || curr.col < 0 || curr.col >= grid[0].size()) {
        return false;
    }
    if (visited->find(curr) != visited->end()) {
        return false;
    }
    int currValue = grid[curr.row][curr.col];
    if (currValue != prevValue + 1) {
        return false;
    }
    if (curr == end) {
        return true;
    }
    visited->insert(curr);
    return isValidTrailHelper(grid, curr.up(), end, currValue, visited) ||
           isValidTrailHelper(grid, curr.right(), end, currValue, visited) ||
           isValidTrailHelper(grid, curr.down(), end, currValue, visited) ||
           isValidTrailHelper(grid, curr.left(), end, currValue, visited);
}

bool isValidTrail(const vector<vector<int>> &grid, Point start, Point end) {
    std::set<Point> visited;
    return isValidTrailHelper(grid, start, end, -1, &visited);
}

void part1(const vector<vector<int>> &grid) {
    vector<Point> starts;
    vector<Point> ends;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            int val = grid[i][j];
            if (val == 0) {
                starts.push_back({i, j});
            } else if (val == 9) {
                ends.push_back({i, j});
            }
        }
    }
    int total = 0;
    for (Point start : starts) {
        for (Point end : ends) {
            if (isValidTrail(grid, start, end)) {
                cout << "Found valid trail from [" << start.row << "," << start.col << "] to [" << end.row << ","
                     << end.col << "]" << endl;
                total += 1;
            }
        }
    }
    cout << "Total: " << total << endl;
}

int getTrailScoreHelper(const vector<vector<int>> &grid, Point curr, Point end, int prevValue,
                        std::set<Point> *visited) {
    if (curr.row < 0 || curr.row >= grid.size() || curr.col < 0 || curr.col >= grid[0].size()) {
        return 0;
    }
    // if (visited->find(curr) != visited->end()) {
    //     return false;
    // }
    int currValue = grid[curr.row][curr.col];
    if (currValue != prevValue + 1) {
        return 0;
    }
    if (curr == end) {
        return 1;
    }
    visited->insert(curr);
    return getTrailScoreHelper(grid, curr.up(), end, currValue, visited) +
           getTrailScoreHelper(grid, curr.right(), end, currValue, visited) +
           getTrailScoreHelper(grid, curr.down(), end, currValue, visited) +
           getTrailScoreHelper(grid, curr.left(), end, currValue, visited);
}

int getTrailScore(const vector<vector<int>> &grid, Point start, Point end) {
    std::set<Point> visited;
    return getTrailScoreHelper(grid, start, end, -1, &visited);
}

void part2(const vector<vector<int>> &grid) {
    vector<Point> starts;
    vector<Point> ends;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            int val = grid[i][j];
            if (val == 0) {
                starts.push_back({i, j});
            } else if (val == 9) {
                ends.push_back({i, j});
            }
        }
    }
    int total = 0;
    for (Point start : starts) {
        for (Point end : ends) {
            int trailScore = getTrailScore(grid, start, end);
            cout << "Score of trail from [" << start.row << "," << start.col << "] to [" << end.row << "," << end.col
                 << "]" << " : " << trailScore << endl;
            total += trailScore;
        }
    }
    cout << "Total: " << total << endl;
}

int main() {
    try {
        vector<vector<int>> matrix = readIntMatrix("input");
        part2(matrix);

    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
