#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

void part1() {}

void part2() {}

int main() {
    try {
        auto startTime = std::chrono::high_resolution_clock::now();

        // Runner block
        vector<string> lines = readLines("sample");

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
