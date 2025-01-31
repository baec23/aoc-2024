#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

struct Velocity {
    long x;
    long y;
};

struct Position {
    long x;
    long y;
};

struct Robot {
    Position position;
    Velocity velocity;
};

/* Quadrant numbers
 *  1   2
 *  3   4
 *
 *  0 if in between quadrants
 */
int findQuadrant(Position p, int gridRows, int gridCols) {
    int rowMid = gridRows / 2;
    int colMid = gridCols / 2;
    int leftStart = 0;
    int leftEnd = colMid;
    int rightStart;
    int rightEnd = gridCols;
    if (gridCols % 2 == 0) {
        rightStart = colMid;
    } else {
        rightStart = colMid + 1;
    }

    int topStart = 0;
    int topEnd = rowMid;
    int botStart;
    int botEnd = gridRows;
    if (gridRows % 2 == 0) {
        botStart = rowMid;
    } else {
        botStart = rowMid + 1;
    }

    // Left half
    if (p.x >= leftStart && p.x < leftEnd) {
        // Top half
        if (p.y >= topStart && p.y < topEnd) {
            return 1;
        }
        // Bottom half
        else if (p.y >= botStart && p.y < botEnd) {
            return 3;
        }
        // In between
        else {
            return 0;
        }
    }
    // Right half
    else if (p.x >= rightStart && p.x < rightEnd) {
        // Top half
        if (p.y >= topStart && p.y < topEnd) {
            return 2;
        }
        // Bottom half
        else if (p.y >= botStart && p.y < botEnd) {
            return 4;
        }
        // In between
        else {
            return 0;
        }
    }
    // In between
    else {
        return 0;
    }
}

void part1(vector<string> lines, int numSeconds, int gridRows, int gridCols) {
    vector<Robot> robots;
    for (string line : lines) {
        vector<string> split = splitStr(line, " ");  // 0=pos , 1=vel
        vector<string> pos = splitStr(splitStr(split[0], "=")[1], ",");
        int posX = stoi(pos[0]);
        int posY = stoi(pos[1]);
        vector<string> vel = splitStr(splitStr(split[1], "=")[1], ",");
        int velX = stoi(vel[0]);
        int velY = stoi(vel[1]);
        robots.push_back({{posX, posY}, {velX, velY}});
    }
    for (Robot& r : robots) {
        r.position.x += r.velocity.x * numSeconds;
        r.position.y += r.velocity.y * numSeconds;
        r.position.x %= gridCols;
        if (r.position.x < 0) {
            r.position.x += gridCols;
        }
        r.position.y %= gridRows;
        if (r.position.y < 0) {
            r.position.y += gridRows;
        }
    }

    // Print
    vector<vector<int>> grid;
    for (int i = 0; i < gridRows; i++) {
        vector<int> row(gridCols);
        grid.push_back(row);
    }
    for (vector<int> row : grid) {
        row = vector<int>(gridCols, 0);
    }

    long quad1Total = 0;
    long quad2Total = 0;
    long quad3Total = 0;
    long quad4Total = 0;
    long noQuadTotal = 0;
    for (Robot r : robots) {
        grid[r.position.y][r.position.x]++;
        int quadrant = findQuadrant(r.position, gridRows, gridCols);
        switch (quadrant) {
            case 0:
                noQuadTotal++;
                break;
            case 1:
                quad1Total++;
                break;
            case 2:
                quad2Total++;
                break;
            case 3:
                quad3Total++;
                break;
            case 4:
                quad4Total++;
                break;
        }
    }
    for (vector<int> row : grid) {
        for (int v : row) {
            if (v == 0) {
                cout << ". ";
            } else {
                cout << v << " ";
            }
        }
        cout << endl;
    }
    cout << "Quadrant totals: " << endl;
    cout << "\t1 : " << quad1Total << endl;
    cout << "\t2 : " << quad2Total << endl;
    cout << "\t3 : " << quad3Total << endl;
    cout << "\t4 : " << quad4Total << endl;
    cout << "\tIn Between : " << noQuadTotal << endl << endl;
    cout << "Safety score : " << quad1Total * quad2Total * quad3Total * quad4Total << endl;
}

void part2(vector<string> lines, int numSeconds, int gridRows, int gridCols) {
    vector<Robot> robots;
    for (string line : lines) {
        vector<string> split = splitStr(line, " ");  // 0=pos , 1=vel
        vector<string> pos = splitStr(splitStr(split[0], "=")[1], ",");
        int posX = stoi(pos[0]);
        int posY = stoi(pos[1]);
        vector<string> vel = splitStr(splitStr(split[1], "=")[1], ",");
        int velX = stoi(vel[0]);
        int velY = stoi(vel[1]);
        robots.push_back({{posX, posY}, {velX, velY}});
    }
    for (Robot& r : robots) {
        r.position.x += r.velocity.x * numSeconds;
        r.position.y += r.velocity.y * numSeconds;
        r.position.x %= gridCols;
        if (r.position.x < 0) {
            r.position.x += gridCols;
        }
        r.position.y %= gridRows;
        if (r.position.y < 0) {
            r.position.y += gridRows;
        }
    }

    // Print
    vector<vector<int>> grid;
    for (int i = 0; i < gridRows; i++) {
        vector<int> row(gridCols);
        grid.push_back(row);
    }
    for (vector<int> row : grid) {
        row = vector<int>(gridCols, 0);
    }

    long quad1Total = 0;
    long quad2Total = 0;
    long quad3Total = 0;
    long quad4Total = 0;
    long noQuadTotal = 0;
    for (Robot r : robots) {
        grid[r.position.y][r.position.x]++;
        int quadrant = findQuadrant(r.position, gridRows, gridCols);
        switch (quadrant) {
            case 0:
                noQuadTotal++;
                break;
            case 1:
                quad1Total++;
                break;
            case 2:
                quad2Total++;
                break;
            case 3:
                quad3Total++;
                break;
            case 4:
                quad4Total++;
                break;
        }
    }
    for (vector<int> row : grid) {
        for (int v : row) {
            if (v == 0) {
                cout << ".";
            } else {
                cout << v;
            }
        }
        cout << endl;
    }
}

int main() {
    try {
        auto startTime = std::chrono::high_resolution_clock::now();

        // Runner block

        vector<string> lines = readLines("input");
        int numSeconds = 0;
        int numTimesDisplayed = 0;
        while (numTimesDisplayed <= 103) {
            if (numSeconds % 101 == 22) {
                cout << "numSeconds = " << numSeconds << endl;
                part2(lines, numSeconds, 103, 101);
                numTimesDisplayed++;
                cout << endl << endl;
            }
            numSeconds++;
        }

        // End Runner block
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        cout << "Time elapsed: " << duration << "ms" << endl;
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
