#include <cstdlib>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

struct Equation {
    long target;
    vector<long> numbers;

    bool operator<(const Equation &other) const {
        if (target != other.target) {
            return target < other.target;
        }
        return numbers < other.numbers;
    }
};

void checkIsValid(std::set<Equation> &validEquations, const Equation &eq, long currTotal, long numbersIndex) {
    cout << "Equation target: " << eq.target << " | currTotal: " << currTotal << " | numbersIndex: " << numbersIndex;
    if (currTotal == eq.target) {
        cout << " | Inserting" << endl;
        validEquations.insert(eq);
        return;
    }
    if (numbersIndex >= eq.numbers.size() || currTotal > eq.target) {
        cout << " | Stopping" << endl;
        return;
    }
    cout << endl;
    // Add
    checkIsValid(validEquations, eq, currTotal + eq.numbers[numbersIndex], numbersIndex + 1);
    // Mult
    checkIsValid(validEquations, eq, currTotal * eq.numbers[numbersIndex], numbersIndex + 1);
}

void checkIsValid2(std::set<Equation> &validEquations, const Equation &eq, long currTotal, long numbersIndex) {
    // cout << "Equation target: " << eq.target << " | currTotal: " << currTotal << " | numbersIndex: " << numbersIndex;
    if (currTotal == eq.target) {
        // cout << " | Inserting" << endl;
        validEquations.insert(eq);
        return;
    }
    if (numbersIndex >= eq.numbers.size() || currTotal > eq.target) {
        // cout << " | Stopping" << endl;
        return;
    }
    // cout << endl;
    // Add
    checkIsValid2(validEquations, eq, currTotal + eq.numbers[numbersIndex], numbersIndex + 1);
    // Mult
    checkIsValid2(validEquations, eq, currTotal * eq.numbers[numbersIndex], numbersIndex + 1);
    // Concat
    string currTotalStr = to_string(currTotal);
    string currNumberStr = to_string(eq.numbers[numbersIndex]);
    string concattedStr = currTotalStr + currNumberStr;
    long concattedNum = std::stol(concattedStr);
    checkIsValid2(validEquations, eq, concattedNum, numbersIndex + 1);
}

void part1(const vector<Equation> &equations) {
    std::set<Equation> validEquations;
    for (auto eq : equations) {
        checkIsValid(validEquations, eq, eq.numbers[0], 1);
    }
    long totalCalibration = 0;
    for (auto validEq : validEquations) {
        totalCalibration += validEq.target;
    }
    cout << "Total calibration result = " << totalCalibration << endl;
}

void part2(const vector<Equation> &equations) {
    std::set<Equation> validEquations;
    for (auto eq : equations) {
        checkIsValid2(validEquations, eq, eq.numbers[0], 1);
    }
    long totalCalibration = 0;
    for (auto validEq : validEquations) {
        totalCalibration += validEq.target;
    }
    cout << "Total calibration result = " << totalCalibration << endl;
}

int main() {
    try {
        vector<string> lines = readLines("input");
        vector<Equation> equations;
        for (auto line : lines) {
            vector<string> split = splitStr(line, ": ");
            long target = std::stol(split[0]);
            vector<string> numberStrings = splitStr(split[1], " ");
            vector<long> numbers;
            for (auto numberString : numberStrings) {
                numbers.push_back(std::stol(numberString));
            }
            equations.push_back({target, numbers});
        }
        part2(equations);

    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
