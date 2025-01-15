#include <cstdlib>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

enum class Direction { Up, Right, Down, Left };

struct Position {
    int row;
    int col;

    bool operator<(const Position& other) const { return (row < other.row) || (row == other.row && col < other.col); }
};

struct PositionWithDirection {
    int row;
    int col;
    Direction direction;

    bool operator<(const PositionWithDirection& other) const {
        if (row != other.row) return row < other.row;
        if (col != other.col) return col < other.col;
        return direction < other.direction;
    }
};

Direction turn(Direction currDirection) {
    switch (currDirection) {
        case Direction::Up:
            return Direction::Right;
        case Direction::Right:
            return Direction::Down;
        case Direction::Down:
            return Direction::Left;
        case Direction::Left:
            return Direction::Up;
    }
}

Position nextPos(Direction currDirection, Position currPosition) {
    switch (currDirection) {
        case Direction::Up:
            return {currPosition.row - 1, currPosition.col};
        case Direction::Right:
            return {currPosition.row, currPosition.col + 1};
        case Direction::Down:
            return {currPosition.row + 1, currPosition.col};
        case Direction::Left:
            return {currPosition.row, currPosition.col - 1};
    }
}

bool causesLoop(vector<vector<char>> grid) {
    Direction currDirection = Direction::Up;
    Position currPosition;
    bool found = false;
    // Find initial position
    for (auto i = 0; i < grid.size() && !found; i++) {
        for (auto j = 0; j < grid[i].size() && !found; j++) {
            if (grid[i][j] == '^') {
                currPosition.row = i;
                currPosition.col = j;
                found = true;
            }
        }
    }
    // Run
    std::set<PositionWithDirection> visited;
    while (true) {
        if (visited.find({currPosition.row, currPosition.col, currDirection}) != visited.end()) {
            // cout << "Found a loop" << endl;
            return true;
        }
        visited.insert({currPosition.row, currPosition.col, currDirection});
        Position next = nextPos(currDirection, currPosition);
        // cout << "CurrPosition : " << currPosition.row << ", " << currPosition.col << " | ";
        if (next.row < 0 || next.row >= grid.size() || next.col < 0 || next.col >= grid[0].size()) {
            // cout << "Not a loop" << endl;
            return false;
        }
        if (grid[next.row][next.col] == '#') {
            // cout << "Turning" << endl;
            currDirection = turn(currDirection);
            continue;
        }
        // cout << "Moving" << endl;
        currPosition = next;
    }
}

std::set<Position> traverse(const vector<vector<char>>& grid) {
    Direction currDirection = Direction::Up;
    Position currPosition;
    bool found = false;
    // Find initial position
    for (auto i = 0; i < grid.size() && !found; i++) {
        for (auto j = 0; j < grid[i].size() && !found; j++) {
            if (grid[i][j] == '^') {
                currPosition.row = i;
                currPosition.col = j;
                found = true;
            }
        }
    }

    // Run
    std::set<Position> visited;
    while (true) {
        visited.insert(currPosition);
        Position next = nextPos(currDirection, currPosition);
        // cout << "CurrPosition : " << currPosition.row << ", " << currPosition.col << " | ";
        if (next.row < 0 || next.row >= grid.size() || next.col < 0 || next.col >= grid[0].size()) {
            // cout << "Out of bounds" << endl;
            break;
        }
        if (grid[next.row][next.col] == '#') {
            // cout << "Turning" << endl;
            currDirection = turn(currDirection);
            continue;
        }
        // cout << "Moving" << endl;
        currPosition = next;
    }

    // cout << "LastPosition = " << currPosition.row << ", " << currPosition.col << endl;
    return visited;
}

void part1(vector<vector<char>> grid) { cout << "Num visited = " << traverse(grid).size() << endl; }

void part2(const vector<vector<char>>& grid) {
    Direction currDirection = Direction::Up;
    Position currPosition;
    int numLoopingChanges = 0;

    std::set<Position> visitedPositions = traverse(grid);
    int numPossiblePositions = visitedPositions.size();
    int numTestedPositions = 0;

    for (auto i = 0; i < grid.size(); i++) {
        for (auto j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '.' && visitedPositions.find({i, j}) != visitedPositions.end()) {
                vector<vector<char>> newGrid(grid);
                newGrid[i][j] = '#';
                if (causesLoop(newGrid)) {
                    numLoopingChanges++;
                }
                numTestedPositions++;
                cout << "Tested " << numTestedPositions << " / " << numPossiblePositions << endl;
            }
        }
    }
    cout << "Num looping changes = " << numLoopingChanges << endl;
}

int main() {
    try {
        vector<vector<char>> matrix = readCharMatrix("input");
        part2(matrix);

    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
