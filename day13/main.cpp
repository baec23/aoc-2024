#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

struct Button {
    int x;
    int y;
};
struct Prize {
    long x;
    long y;
};

struct ClawMachine {
    Button aButton;
    Button bButton;
    Prize prize;
};

int extractNumber(const string &s) {
    std::regex numberRegex("\\d+");
    std::smatch match;
    if (std::regex_search(s, match, numberRegex)) {
        return std::stoi(match.str());
    }
    return -1;
}

vector<ClawMachine> parseInput(const vector<string> &lines) {
    vector<ClawMachine> clawMachines;
    int groupLineIndex = 0;  // 0 is aButton, 1 is bButton, 2 is prize || empty line restarts
    ClawMachine *pCurrClawMachine;
    for (string line : lines) {
        if (line.empty()) {
            groupLineIndex = 0;
            continue;
        }
        if (groupLineIndex == 0) {
            ClawMachine curr = {{0, 0}, {0, 0}, {0, 0}};
            pCurrClawMachine = &curr;
        }
        vector<string> splitLine = splitStr(line, " ");
        // X always second to last and Y always last
        string xString = splitLine[splitLine.size() - 2];
        string yString = splitLine[splitLine.size() - 1];
        int x = extractNumber(xString);
        int y = extractNumber(yString);
        // aButton
        if (groupLineIndex == 0) {
            pCurrClawMachine->aButton = {x, y};
        } else if (groupLineIndex == 1) {
            pCurrClawMachine->bButton = {x, y};
        } else {
            pCurrClawMachine->prize = {x, y};
            clawMachines.push_back(*pCurrClawMachine);
        }
        groupLineIndex++;
    }
    return clawMachines;
}

vector<ClawMachine> parseInput2(const vector<string> &lines) {
    vector<ClawMachine> clawMachines;
    int groupLineIndex = 0;  // 0 is aButton, 1 is bButton, 2 is prize || empty line restarts
    ClawMachine *pCurrClawMachine;
    for (string line : lines) {
        if (line.empty()) {
            groupLineIndex = 0;
            continue;
        }
        if (groupLineIndex == 0) {
            ClawMachine curr = {{0, 0}, {0, 0}, {0, 0}};
            pCurrClawMachine = &curr;
        }
        vector<string> splitLine = splitStr(line, " ");
        // X always second to last and Y always last
        string xString = splitLine[splitLine.size() - 2];
        string yString = splitLine[splitLine.size() - 1];
        int x = extractNumber(xString);
        int y = extractNumber(yString);
        // aButton
        if (groupLineIndex == 0) {
            pCurrClawMachine->aButton = {x, y};
        } else if (groupLineIndex == 1) {
            pCurrClawMachine->bButton = {x, y};
        } else {
            pCurrClawMachine->prize = {x + 10000000000000, y + 10000000000000};
            clawMachines.push_back(*pCurrClawMachine);
        }
        groupLineIndex++;
    }
    return clawMachines;
}

bool isWholeNumber(double num) { return std::floor(num) == num; }
void part1(const vector<string> &lines) {
    vector<ClawMachine> clawMachines = parseInput(lines);

    long totalTokens = 0;
    for (ClawMachine c : clawMachines) {
        double aPresses = ((double)((-1 * c.bButton.x) * c.prize.y) + (c.prize.x * c.bButton.y)) /
                          ((c.aButton.x * c.bButton.y) - (c.bButton.x * c.aButton.y));
        double bPresses = ((double)(c.aButton.x * c.prize.y) - (c.prize.x * c.aButton.y)) /
                          ((c.aButton.x * c.bButton.y) - (c.bButton.x * c.aButton.y));
        cout << "a, b = " << aPresses << ", " << bPresses << endl;
        if (isWholeNumber(aPresses) && isWholeNumber(bPresses)) {
            totalTokens += std::floor(aPresses) * 3;
            totalTokens += std::floor(bPresses);
        }
    }
    cout << "Total presses = " << totalTokens << endl;
}

void part2(const vector<string> &lines) {
    vector<ClawMachine> clawMachines = parseInput2(lines);

    long totalTokens = 0;
    for (ClawMachine c : clawMachines) {
        double aPresses = ((double)((-1 * c.bButton.x) * c.prize.y) + (c.prize.x * c.bButton.y)) /
                          ((c.aButton.x * c.bButton.y) - (c.bButton.x * c.aButton.y));
        double bPresses = ((double)(c.aButton.x * c.prize.y) - (c.prize.x * c.aButton.y)) /
                          ((c.aButton.x * c.bButton.y) - (c.bButton.x * c.aButton.y));
        cout << "a, b = " << aPresses << ", " << bPresses << endl;
        if (isWholeNumber(aPresses) && isWholeNumber(bPresses)) {
            totalTokens += std::floor(aPresses) * 3;
            totalTokens += std::floor(bPresses);
        }
    }
    cout << "Total presses = " << totalTokens << endl;
}

int main() {
    try {
        auto startTime = std::chrono::high_resolution_clock::now();

        // Runner block
        vector<string> lines = readLines("input");
        part2(lines);

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
