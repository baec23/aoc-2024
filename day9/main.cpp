#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

// start inclusive, end exclusive
struct DiskFragment {
    int start;
    int end;
    int getLength() { return end - start; };
};

int findFreeBlock(const vector<int> &decoded, int start = 0) {
    for (int i = start; i < decoded.size(); i++) {
        if (decoded[i] == -1) {
            return i;
        }
    }
    return -1;
}
int findFileToMove(const vector<int> &decoded, int start) {
    for (int i = start; i >= 0; i--) {
        if (decoded[i] != -1) {
            return i;
        }
    }
    return -1;
}

void part1(const string &line) {
    vector<int> decoded;
    bool isFile = true;
    int currFileId = 0;
    long numFiles = 0;

    for (int i = 0; i < line.size(); i++) {
        int digit = line[i] - '0';
        int val = -1;
        if (isFile) {
            val = currFileId;
            currFileId++;
        }
        for (int j = 0; j < digit; j++) {
            decoded.push_back(val);
        }
        isFile = !isFile;
    }
    int freeBlockIndex = findFreeBlock(decoded, 0);
    int fileToMoveIndex = findFileToMove(decoded, decoded.size() - 1);
    while (freeBlockIndex < fileToMoveIndex) {
        decoded[freeBlockIndex] = decoded[fileToMoveIndex];
        decoded[fileToMoveIndex] = -1;
        freeBlockIndex = findFreeBlock(decoded, freeBlockIndex + 1);
        fileToMoveIndex = findFileToMove(decoded, fileToMoveIndex - 1);
    }
    // printVec(decoded);
    // cout << "FREE BLOCK INDEX = " << freeBlockIndex << " | FILE TO MOVE INDEX = " << fileToMoveIndex << endl;
    long long toReturn = 0;
    cout << "FREE BLOCK INDEX = " << freeBlockIndex << endl;
    for (int i = 0; i < freeBlockIndex; i++) {
        toReturn += (long)decoded[i] * i;
    }
    cout << "checksum= " << toReturn << endl;
}

void part2(const string &line) {
    bool isFile = true;
    int currFileId = 0;
    int currIndex = 0;

    vector<DiskFragment> files;
    vector<DiskFragment> freeSpaces;

    for (char c : line) {
        int digit = c - '0';
        int start = currIndex;
        int end = currIndex + digit;
        DiskFragment fragment = {start, end};
        currIndex = end;
        if (fragment.getLength() <= 0) {
            // cout << "Skipping because length is 0: digit, isFile: " << digit << ", " << isFile << endl;
        } else {
            if (isFile) {
                files.push_back(fragment);
                // cout << "Adding file from range [" << start << ", " << end << ") and length = " <<
                // fragment.getLength()
                //      << endl;
            } else {
                freeSpaces.push_back(fragment);
                // cout << "Adding freeSpace from range [" << start << ", " << end
                //      << ") and length = " << fragment.getLength() << endl;
            }
        }
        isFile = !isFile;
    }

    cout << "Files..." << endl;
    for (int i = 0; i < files.size(); i++) {
        cout << "\tFile " << i << ": [" << files[i].start << ", " << files[i].end << "]" << endl;
    }
    cout << "Empty Spaces..." << endl;
    for (int i = 0; i < freeSpaces.size(); i++) {
        cout << "\tFree Space " << i << ": [" << freeSpaces[i].start << ", " << freeSpaces[i].end << "]" << endl;
    }
    for (int i = files.size() - 1; i >= 0; i--) {
        int fileId = i;
        DiskFragment file = files[i];
        for (int j = 0; j < freeSpaces.size(); j++) {
            DiskFragment freeSpace = freeSpaces[j];
            if (freeSpace.start > file.start) {
                break;
            }
            if (file.getLength() <= freeSpace.getLength()) {
                freeSpaces[j] = {freeSpace.start + file.getLength(), freeSpace.end};
                files[i] = {freeSpace.start, freeSpace.start + file.getLength()};
                cout << "Moving file " << fileId << " to " << freeSpace.start << " | remainingFreeSpace = ["
                     << freeSpaces[j].start << ", " << freeSpaces[j].end << "]" << endl;
                break;
            }
        }
    }
    // cout << "Files..." << endl;
    // for (int i = 0; i < files.size(); i++) {
    //     cout << "\tFile " << i << ": [" << files[i].start << ", " << files[i].end << "]" << endl;
    // }
    // cout << "Empty Spaces..." << endl;
    // for (int i = 0; i < freeSpaces.size(); i++) {
    //     cout << "\tFree Space " << i << ": [" << freeSpaces[i].start << ", " << freeSpaces[i].end << "]" << endl;
    // }

    // Calc checksum
    long toReturn = 0;
    for (int i = 0; i < files.size(); i++) {
        DiskFragment file = files[i];
        for (int j = file.start; j < file.end; j++) {
            toReturn += i * j;
        }
    }
    cout << "Checksum = " << toReturn << endl;
}

int main() {
    try {
        vector<string> lines = readLines("input");
        string line = lines[0];
        part2(line);

    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
