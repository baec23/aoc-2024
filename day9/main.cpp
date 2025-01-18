#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

struct DiskFragment {
    int startIndex;
    int endIndex;
    int getLength() { return std::max(0, endIndex - startIndex); };
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
    printVec(decoded);
    cout << "FREE BLOCK INDEX = " << freeBlockIndex << " | FILE TO MOVE INDEX = " << fileToMoveIndex << endl;
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
        int startIndex = currIndex;
        int endIndex = currIndex + digit - 1;
        DiskFragment fragment = {startIndex, endIndex};
        // cout << "Adding fragment from range [" << startIndex << ", " << endIndex
        //      << "] and length =" << fragment.getLength() << endl;
        currIndex = endIndex + 1;
        if (isFile) {
            files.push_back(fragment);
        } else {
            freeSpaces.push_back(fragment);
        }
        isFile = !isFile;
    }
    // cout << "Files..." << endl;
    // for (int i = 0; i < files.size(); i++) {
    //     cout << "\tFile " << i << ": [" << files[i].startIndex << ", " << files[i].endIndex << "]" << endl;
    // }
    // cout << "Empty Spaces..." << endl;
    // for (int i = 0; i < freeSpaces.size(); i++) {
    //     cout << "\tFree Space " << i << ": [" << freeSpaces[i].startIndex << ", " << freeSpaces[i].endIndex << "]"
    //          << endl;
    // }
    for (int i = files.size() - 1; i >= 0; i--) {
        int fileId = i;
        DiskFragment file = files[i];
        for (int j = 0; j < freeSpaces.size(); j++) {
            DiskFragment freeSpace = freeSpaces[j];
            if (freeSpace.startIndex > file.startIndex) {
                break;
            }
            if (file.getLength() <= freeSpace.getLength()) {
                freeSpaces[j] = {freeSpace.startIndex + file.getLength() + 1, freeSpace.endIndex};
                files[i] = {freeSpace.startIndex, freeSpace.startIndex + file.getLength()};
                // cout << "Moving file " << fileId << " to " << freeSpace.startIndex << " | remainingFreeSpace = ["
                //      << freeSpaces[j].startIndex << ", " << freeSpaces[j].endIndex << "]" << endl;
                break;
            }
        }
    }
    cout << "Files..." << endl;
    for (int i = 0; i < files.size(); i++) {
        cout << "\tFile " << i << ": [" << files[i].startIndex << ", " << files[i].endIndex << "]" << endl;
    }
    cout << "Empty Spaces..." << endl;
    for (int i = 0; i < freeSpaces.size(); i++) {
        cout << "\tFree Space " << i << ": [" << freeSpaces[i].startIndex << ", " << freeSpaces[i].endIndex << "]"
             << endl;
    }

    // Calc checksum
    long toReturn = 0;
    for (int i = 0; i < files.size(); i++) {
        DiskFragment file = files[i];
        for (int j = file.startIndex; j <= file.endIndex; j++) {
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
