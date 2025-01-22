#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

using Stone = deque<int>;

Stone stringToStone(const string &numberString) {
    Stone toReturn;
    for (char c : numberString) {
        toReturn.push_back(charToInt(c));
    }
    return toReturn;
}

Stone removeLeadingZeroes(const Stone &stone) {
    Stone toReturn;
    int startIndex = 0;
    while (startIndex < stone.size() - 1 && stone[startIndex] == 0) {
        startIndex++;
    }
    for (int i = startIndex; i < stone.size(); i++) {
        toReturn.push_back(stone[i]);
    }
    return toReturn;
}

string removeLeadingZeroes(const string &in) {
    size_t startIndex = 0;
    while (startIndex < in.size() && in[startIndex] == '0') {
        startIndex++;
    }
    if (startIndex == in.size()) {
        return "0";
    }
    return in.substr(startIndex);
}

string add(const string &aStr, const string &bStr) {
    deque<int> a = stringToStone(aStr);
    deque<int> b = stringToStone(bStr);
    deque<int> toReturn;
    int maxLength = max(a.size(), b.size());
    int carry = 0;
    for (int i = 1; i <= maxLength; i++) {
        int aValue, bValue;
        int aIndex = a.size() - i;
        int bIndex = b.size() - i;
        if (aIndex < 0) {
            aValue = 0;
        } else {
            aValue = a[aIndex];
        }
        if (bIndex < 0) {
            bValue = 0;
        } else {
            bValue = b[bIndex];
        }
        int sum = aValue + bValue + carry;
        string sumString = to_string(sum);
        toReturn.push_front(charToInt(sumString[sumString.size() - 1]));
        string carryString = sumString.substr(0, sumString.size() - 1);
        if (carryString.size() > 0) {
            carry = stoi(carryString);
        } else {
            carry = 0;
        }
    }
    if (carry != 0) {
        string carryString = to_string(carry);
        for (int i = carryString.size() - 1; i >= 0; i--) {
            toReturn.push_front(charToInt(carryString[i]));
        }
    }
    return dequeToString(toReturn);
}

Stone add(const Stone &a, const Stone &b) {
    Stone toReturn;
    int maxLength = max(a.size(), b.size());
    int carry = 0;
    for (int i = 1; i <= maxLength; i++) {
        int aValue, bValue;
        int aIndex = a.size() - i;
        int bIndex = b.size() - i;
        if (aIndex < 0) {
            aValue = 0;
        } else {
            aValue = a[aIndex];
        }
        if (bIndex < 0) {
            bValue = 0;
        } else {
            bValue = b[bIndex];
        }
        int sum = aValue + bValue + carry;
        string sumString = to_string(sum);
        toReturn.push_front(charToInt(sumString[sumString.size() - 1]));
        string carryString = sumString.substr(0, sumString.size() - 1);
        if (carryString.size() > 0) {
            carry = stoi(carryString);
        } else {
            carry = 0;
        }
    }
    if (carry != 0) {
        string carryString = to_string(carry);
        for (int i = carryString.size() - 1; i >= 0; i--) {
            toReturn.push_front(charToInt(carryString[i]));
        }
    }
    return toReturn;
}

string mult(const string &aStr, const string &bStr) {
    deque<int> a = stringToStone(aStr);
    deque<int> b = stringToStone(bStr);
    deque<int> multResults[b.size()];
    int dequeIndex = 0;

    // cout << "Multiplying..." << endl;
    // cout << "Stone a: " << dequeToString(a) << " | Stone b: " << dequeToString(b) << endl;

    for (int i = b.size() - 1; i >= 0; i--) {
        int carry = 0;
        int multiplicand = b[i];
        for (int j = 0; j < dequeIndex; j++) {
            multResults[dequeIndex].push_front(0);
        }
        for (int j = a.size() - 1; j >= 0; j--) {
            int multiplier = a[j];
            int product = multiplicand * multiplier;
            product += carry;
            string productString = to_string(product);
            if (productString.size() > 1) {
                carry = charToInt(productString[0]);
                multResults[dequeIndex].push_front(charToInt(productString[1]));
            } else {
                carry = 0;
                multResults[dequeIndex].push_front(charToInt(productString[0]));
            }
        }
        if (carry != 0) {
            multResults[dequeIndex].push_front(carry);
        }
        dequeIndex++;
    }

    deque<int> toReturn = multResults[0];
    for (int i = 1; i < b.size(); i++) {
        toReturn = add(toReturn, multResults[i]);
    }
    return dequeToString(toReturn);
}
Stone mult(const Stone &a, const Stone &b) {
    Stone multResults[b.size()];
    int dequeIndex = 0;

    // cout << "Multiplying..." << endl;
    // cout << "Stone a: " << dequeToString(a) << " | Stone b: " << dequeToString(b) << endl;

    for (int i = b.size() - 1; i >= 0; i--) {
        int carry = 0;
        int multiplicand = b[i];
        for (int j = 0; j < dequeIndex; j++) {
            multResults[dequeIndex].push_front(0);
        }
        for (int j = a.size() - 1; j >= 0; j--) {
            int multiplier = a[j];
            int product = multiplicand * multiplier;
            product += carry;
            string productString = to_string(product);
            if (productString.size() > 1) {
                carry = charToInt(productString[0]);
                multResults[dequeIndex].push_front(charToInt(productString[1]));
            } else {
                carry = 0;
                multResults[dequeIndex].push_front(charToInt(productString[0]));
            }
        }
        if (carry != 0) {
            multResults[dequeIndex].push_front(carry);
        }
        dequeIndex++;
    }

    Stone toReturn = multResults[0];
    for (int i = 1; i < b.size(); i++) {
        toReturn = add(toReturn, multResults[i]);
    }
    return toReturn;
}

vector<Stone> blink(const vector<Stone> &stones) {
    vector<Stone> toReturn;
    for (Stone stone : stones) {
        string stoneString = dequeToString(stone);
        vector<Stone> nextStones;
        if (stone.size() == 1 && stone[0] == 0) {
            nextStones.push_back({1});
            // cout << "0 becomes 1" << endl;
        } else if (stone.size() % 2 == 0) {
            Stone leftStone, rightStone;
            int midIndex = stone.size() / 2;
            for (int i = 0; i < midIndex; i++) {
                leftStone.push_back(stone[i]);
            }
            for (int i = midIndex; i < stone.size(); i++) {
                rightStone.push_back(stone[i]);
            }
            nextStones.push_back(removeLeadingZeroes(leftStone));
            nextStones.push_back(removeLeadingZeroes(rightStone));
            // cout << "(split) becomes " << dequeToString(leftStone) << " and " << dequeToString(rightStone) <<
            // endl;
        } else {
            Stone multiplier = stringToStone("2024");
            Stone multResult = mult(stone, multiplier);
            nextStones.push_back(multResult);
            // cout << "(mult) becomes " << dequeToString(multResult) << endl;
        }
        for (Stone s : nextStones) {
            toReturn.push_back(s);
        }
    }
    return toReturn;
}

void part1(const vector<string> &strings) {
    vector<Stone> stones;
    for (string s : strings) {
        stones.push_back(stringToStone(s));
    }

    cout << "Initial stones: " << endl;
    for (Stone s : stones) {
        cout << dequeToString(s) << " ";
    }
    cout << endl;

    int numBlinks = 25;
    for (int i = 0; i < numBlinks; i++) {
        stones = blink(stones);
    }

    cout << endl << "Number of stones after " << numBlinks << ": " << stones.size() << endl;
}

std::map<string, string> blink2(const std::map<string, string> &numStonesMap) {
    std::map<string, string> toReturn;
    for (const auto &pair : numStonesMap) {
        string stone = pair.first;
        string count = pair.second;
        if (stone == "0") {
            string nextStone = "1";
            if (toReturn.find(nextStone) == toReturn.end()) {
                toReturn[nextStone] = "0";
            }
            toReturn[nextStone] = add(toReturn[nextStone], count);
        } else if (stone.size() % 2 == 0) {
            int splitSize = stone.size() / 2;
            string leftStone = removeLeadingZeroes(stone.substr(0, splitSize));
            string rightStone = removeLeadingZeroes(stone.substr(splitSize, splitSize));
            if (toReturn.find(leftStone) == toReturn.end()) {
                toReturn[leftStone] = "0";
            }
            if (toReturn.find(rightStone) == toReturn.end()) {
                toReturn[rightStone] = "0";
            }
            toReturn[leftStone] = add(toReturn[leftStone], count);
            toReturn[rightStone] = add(toReturn[rightStone], count);
        } else {
            string nextStone = mult(stone, "2024");
            if (toReturn.find(nextStone) == toReturn.end()) {
                toReturn[nextStone] = "0";
            }
            toReturn[nextStone] = add(toReturn[nextStone], count);
        }
    }
    return toReturn;
}

void part2(const vector<string> &strings) {
    std::map<string, string> numStonesMap;
    for (string s : strings) {
        if (numStonesMap.find(s) == numStonesMap.end()) {
            numStonesMap[s] = "0";
        }
        numStonesMap[s] = add(numStonesMap[s], "1");
    }

    int numBlinks = 75;
    for (int i = 0; i < numBlinks; i++) {
        numStonesMap = blink2(numStonesMap);
    }
    cout << "After " << numBlinks << " blinks: " << endl;
    string total = "0";
    for (auto pair : numStonesMap) {
        cout << "\t" << pair.first << " : " << pair.second << endl;
    }
    for (auto pair : numStonesMap) {
        total = add(total, pair.second);
    }
    cout << "\tTotal Num Stones = " << total << endl;
}

int main() {
    try {
        vector<string> lines = readLines("input");
        part2(splitStr(lines[0], " "));

    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
