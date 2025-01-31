#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

enum Direction { UP, RIGHT, DOWN, LEFT };

Point tryMove(vector<vector<char>> *grid, Point robot, Direction direction) {
    Point currPoint;
    switch (direction) {
        case UP:
            currPoint = {robot.row - 1, robot.col};
            while ((*grid)[currPoint.row][currPoint.col] != '.') {
                if ((*grid)[currPoint.row][currPoint.col] == '#') {
                    return robot;
                }
                currPoint = {currPoint.row - 1, currPoint.col};
            }
            for (int row = robot.row - 2; row >= currPoint.row; row--) {
                (*grid)[row][robot.col] = 'O';
            }
            return {robot.row - 1, robot.col};
            break;
        case RIGHT:
            currPoint = {robot.row, robot.col + 1};
            while ((*grid)[currPoint.row][currPoint.col] != '.') {
                if ((*grid)[currPoint.row][currPoint.col] == '#') {
                    return robot;
                }
                currPoint = {currPoint.row, currPoint.col + 1};
            }
            for (int col = robot.col + 2; col <= currPoint.col; col++) {
                (*grid)[robot.row][col] = 'O';
            }
            return {robot.row, robot.col + 1};
            break;
        case DOWN:
            currPoint = {robot.row + 1, robot.col};
            while ((*grid)[currPoint.row][currPoint.col] != '.') {
                if ((*grid)[currPoint.row][currPoint.col] == '#') {
                    return robot;
                }
                currPoint = {currPoint.row + 1, currPoint.col};
            }
            for (int row = robot.row + 2; row <= currPoint.row; row++) {
                (*grid)[row][robot.col] = 'O';
            }
            return {robot.row + 1, robot.col};
            break;
        case LEFT:
            currPoint = {robot.row, robot.col - 1};
            while ((*grid)[currPoint.row][currPoint.col] != '.') {
                if ((*grid)[currPoint.row][currPoint.col] == '#') {
                    return robot;
                }
                currPoint = {currPoint.row, currPoint.col - 1};
            }
            for (int col = robot.col - 2; col >= currPoint.col; col--) {
                (*grid)[robot.row][col] = 'O';
            }
            return {robot.row, robot.col - 1};
            break;
    }
}

void part1(vector<vector<char>> grid, const string &instructions) {
    // Find robot start
    Point robot;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                robot = {i, j};
                grid[i][j] = '.';
                break;
            }
        }
    }

    for (char instruction : instructions) {
        switch (instruction) {
            case '^':
                robot = tryMove(&grid, robot, UP);
                break;
            case '>':
                robot = tryMove(&grid, robot, RIGHT);
                break;
            case 'v':
                robot = tryMove(&grid, robot, DOWN);
                break;
            case '<':
                robot = tryMove(&grid, robot, LEFT);
                break;
        }
        grid[robot.row][robot.col] = '.';
    }

    for (vector<char> row : grid) {
        printVec(row);
    }

    long answer = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                answer += (100 * i) + j;
            }
        }
    }
    cout << "Answer = " << answer << endl;
}

struct Box {
    int boxId;
    int row;
    int colStart;
    int colEnd;
    vector<Box> neighbors(const vector<vector<int>> &adjustedGrid, const map<int, Box> &boxMap, Direction direction) {
        set<int> neighborBoxIds;
        vector<Box> toReturn;
        switch (direction) {
            case UP:
                if (adjustedGrid[row - 1][colStart] > 0) {
                    neighborBoxIds.insert(adjustedGrid[row - 1][colStart]);
                }
                if (adjustedGrid[row - 1][colEnd] > 0) {
                    neighborBoxIds.insert(adjustedGrid[row - 1][colEnd]);
                }
                break;
            case RIGHT:
                if (adjustedGrid[row][colEnd + 1] > 0) {
                    neighborBoxIds.insert(adjustedGrid[row][colEnd + 1]);
                }
                break;
            case DOWN:
                if (adjustedGrid[row + 1][colStart] > 0) {
                    neighborBoxIds.insert(adjustedGrid[row + 1][colStart]);
                }
                if (adjustedGrid[row + 1][colEnd] > 0) {
                    neighborBoxIds.insert(adjustedGrid[row + 1][colEnd]);
                }
                break;
            case LEFT:
                if (adjustedGrid[row][colStart - 1] > 0) {
                    neighborBoxIds.insert(adjustedGrid[row][colStart - 1]);
                }
                break;
        }
        for (int neighborId : neighborBoxIds) {
            toReturn.push_back(boxMap.at(neighborId));
        }
        return toReturn;
    };

    // bool canMove(const vector<vector<int>> &adjustedGrid, Direction direction) {
    //     switch (direction) {
    //         case UP:
    //             if (adjustedGrid[row - 1][colStart] == 0 && adjustedGrid[row - 1][colEnd] == 0) {
    //                 return true;
    //             }
    //             break;
    //         case RIGHT:
    //             if (adjustedGrid[row][colEnd + 1] == 0) {
    //                 return true;
    //             }
    //             break;
    //         case DOWN:
    //             if (adjustedGrid[row + 1][colStart] == 0 && adjustedGrid[row + 1][colEnd] == 0) {
    //                 return true;
    //             }
    //             break;
    //         case LEFT:
    //             if (adjustedGrid[row][colStart - 1] == 0) {
    //                 return true;
    //             }
    //             break;
    //     }
    //     return false;
    // }

    bool maybeCanMove(const vector<vector<int>> &adjustedGrid, const map<int, Box> &boxMap, Direction direction) {
        switch (direction) {
            case UP:
                if (adjustedGrid[row - 1][colStart] == -1 || adjustedGrid[row - 1][colEnd] == -1) {
                    return false;
                }
                break;
            case RIGHT:
                if (adjustedGrid[row][colEnd + 1] == -1) {
                    return false;
                }
                break;
            case DOWN:
                if (adjustedGrid[row + 1][colStart] == -1 || adjustedGrid[row + 1][colEnd] == -1) {
                    return false;
                }
                break;
            case LEFT:
                if (adjustedGrid[row][colStart - 1] == -1) {
                    return false;
                }
                break;
        }
        bool toReturn = true;
        vector<Box> myNeighbors = neighbors(adjustedGrid, boxMap, direction);
        for (Box neighbor : myNeighbors) {
            toReturn = toReturn && neighbor.maybeCanMove(adjustedGrid, boxMap, direction);
        }
        return toReturn;
    }
};

Box tryMove2(vector<vector<int>> *grid, map<int, Box> *boxMap, Box box, Direction direction) {
    // find neighbors
    // tryMove neighbors
    // if canMove, move
    bool canMove = box.maybeCanMove(*grid, *boxMap, direction);
    if (!canMove) {
        return box;
    }
    vector<Box> neighbors = box.neighbors(*grid, *boxMap, direction);
    for (Box neighbor : neighbors) {
        tryMove2(grid, boxMap, neighbor, direction);
    }

    Box newBox;
    switch (direction) {
        case UP:
            newBox = {box.boxId, box.row - 1, box.colStart, box.colEnd};
            break;
        case RIGHT:
            newBox = {box.boxId, box.row, box.colStart + 1, box.colEnd + 1};
            break;
        case DOWN:
            newBox = {box.boxId, box.row + 1, box.colStart, box.colEnd};
            break;
        case LEFT:
            newBox = {box.boxId, box.row, box.colStart - 1, box.colEnd - 1};
            break;
    }
    (*grid)[box.row][box.colStart] = 0;
    (*grid)[box.row][box.colEnd] = 0;
    (*boxMap)[box.boxId] = newBox;
    (*grid)[newBox.row][newBox.colStart] = newBox.boxId;
    (*grid)[newBox.row][newBox.colEnd] = newBox.boxId;
    return newBox;
}

void printGrid(const vector<vector<int>> &grid, char instruction, Box robot) {
    cout << "Instruction " << instruction << endl;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (i == robot.row && j == robot.colStart) {
                cout << '@' << "\t";
            } else if (grid[i][j] == -1) {
                cout << '#' << "\t";
            } else if (grid[i][j] == 0) {
                cout << '.' << "\t";
            } else {
                cout << grid[i][j] << "\t";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void part2(vector<vector<char>> grid, const string &instructions) {
    Box robot;
    // Create grid
    vector<vector<int>> adjustedGrid;
    map<int, Box> boxMap;
    int boxId = 1;
    for (int i = 0; i < grid.size(); i++) {
        adjustedGrid.push_back(vector<int>());
        for (char val : grid[i]) {
            switch (val) {
                case '#':
                    adjustedGrid[i].push_back(-1);
                    adjustedGrid[i].push_back(-1);
                    break;
                case '.':
                    adjustedGrid[i].push_back(0);
                    adjustedGrid[i].push_back(0);
                    break;
                case 'O':
                    boxMap[boxId] = {boxId, i, (int)adjustedGrid[i].size(), (int)adjustedGrid[i].size() + 1};
                    adjustedGrid[i].push_back(boxId);
                    adjustedGrid[i].push_back(boxId);
                    boxId++;
                    break;
                case '@':
                    robot = {-2, i, (int)adjustedGrid[i].size(), (int)adjustedGrid[i].size()};
                    adjustedGrid[i].push_back(0);
                    adjustedGrid[i].push_back(0);
                    break;
            }
        }
    }

    printGrid(adjustedGrid, 'X', robot);
    // Run instructions
    for (char instruction : instructions) {
        switch (instruction) {
            case '^':
                robot = tryMove2(&adjustedGrid, &boxMap, robot, UP);
                break;
            case '>':
                robot = tryMove2(&adjustedGrid, &boxMap, robot, RIGHT);
                break;
            case 'v':
                robot = tryMove2(&adjustedGrid, &boxMap, robot, DOWN);
                break;
            case '<':
                robot = tryMove2(&adjustedGrid, &boxMap, robot, LEFT);
                break;
        }
        // printGrid(adjustedGrid, instruction, robot);
        // cout << endl;
    }

    // Print end grid state
    // for (vector<int> row : adjustedGrid) {
    //     printVec(row);
    // }

    // Calculate answer
    long answer = 0;
    for (auto entry : boxMap) {
        if (entry.first > 0) {
            int row = entry.second.row;
            int col = entry.second.colStart;
            answer += entry.second.row * 100 + entry.second.colStart;
        }
    }
    cout << "Answer = " << answer << endl;
}

int main() {
    try {
        auto startTime = std::chrono::high_resolution_clock::now();

        // Runner block
        vector<string> lines = readLines("input");
        vector<vector<char>> matrix;
        string instructions = "";
        bool gridFinished = false;
        int gridRow = 0;
        for (string line : lines) {
            if (line.empty()) {
                gridFinished = true;
                continue;
            }
            if (gridFinished) {
                instructions += line;
            } else {
                matrix.push_back(vector<char>());
                copy(line.begin(), line.end(), back_inserter(matrix[gridRow]));
                gridRow++;
            }
        }
        // part1(matrix, instructions);
        part2(matrix, instructions);

        // End Runner block

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        cout << "Time elapsed: " << duration << "ms" << endl;
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
