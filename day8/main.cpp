#include <cstdlib>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

struct Position {
    int row;
    int col;

    bool operator<(const Position &other) const { return (row < other.row) || (row == other.row && col < other.col); }
};

vector<Position> findAntinodes(Position a, Position b, int maxRow, int maxCol) {
    vector<Position> toReturn;
    int rowDiff = b.row - a.row;
    int colDiff = b.col - a.col;
    Position potentialPos1 = {a.row - rowDiff, a.col - colDiff};
    if (potentialPos1.row >= 0 && potentialPos1.row <= maxRow && potentialPos1.col >= 0 &&
        potentialPos1.col <= maxCol) {
        toReturn.push_back(potentialPos1);
    }
    Position potentialPos2 = {b.row + rowDiff, b.col + colDiff};
    if (potentialPos2.row >= 0 && potentialPos2.row <= maxRow && potentialPos2.col >= 0 &&
        potentialPos2.col <= maxCol) {
        toReturn.push_back(potentialPos2);
    }
    return toReturn;
}

float findRow(int col, Position a, float slope) { return slope * (col - a.col) + a.row; }

vector<Position> findAntinodes2(Position a, Position b, int maxRow, int maxCol) {
    vector<Position> toReturn;

    if (a.row == b.row) {
        for (int i = 0; i <= maxCol; i++) {
            toReturn.push_back({a.row, i});
        }
        return toReturn;
    }
    if (a.col == b.col) {
        for (int i = 0; i <= maxRow; i++) {
            toReturn.push_back({i, a.col});
        }
        return toReturn;
    }

    float slope = (float)(b.row - a.row) / (b.col - a.col);
    for (int i = 0; i <= maxCol; i++) {
        float rowFloat = findRow(i, a, slope);
        int rowInt = static_cast<int>(rowFloat);
        if (rowFloat == rowInt && rowInt >= 0 && rowInt <= maxRow) {
            toReturn.push_back({rowInt, i});
        }
    }
    return toReturn;
}

void part1(const vector<vector<char>> &grid) {
    std::map<char, vector<Position>> antennas;
    std::set<Position> antinodePositions;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] != '.') {
                char currAntenna = grid[i][j];
                Position currAntennaPosition = {i, j};
                for (auto otherPosition : antennas[currAntenna]) {
                    vector<Position> antinodes =
                        findAntinodes(currAntennaPosition, otherPosition, grid.size() - 1, grid[i].size() - 1);
                    for (auto antinode : antinodes) {
                        antinodePositions.insert(antinode);
                    }
                }
                antennas[currAntenna].push_back(currAntennaPosition);
            }
        }
    }
    cout << "Num antinode positions = " << antinodePositions.size() << endl;
}

void part2(const vector<vector<char>> &grid) {
    std::map<char, vector<Position>> antennas;
    std::set<Position> antinodePositions;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] != '.') {
                char currAntenna = grid[i][j];
                Position currAntennaPosition = {i, j};
                for (auto otherPosition : antennas[currAntenna]) {
                    vector<Position> antinodes =
                        findAntinodes2(currAntennaPosition, otherPosition, grid.size() - 1, grid[i].size() - 1);

                    for (auto antinode : antinodes) {
                        antinodePositions.insert(antinode);
                    }
                }
                antennas[currAntenna].push_back(currAntennaPosition);
            }
        }
    }
    for (auto pos : antinodePositions) {
        cout << "Antinode at: (" << pos.row << ", " << pos.col << ")" << endl;
    }
    cout << "Num antinode positions = " << antinodePositions.size() << endl;
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
