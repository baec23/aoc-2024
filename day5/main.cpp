#include <cstdlib>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "../util/InputUtil.h"

using namespace std;

struct Update {
    vector<int> pages;
    std::set<int> includedPages;
};

vector<int> findValidPages(std::map<int, vector<int>> dependencies, const std::set<int> &includedPages,
                           const std::set<int> &addedPages, vector<int> pages) {
    vector<int> toReturn;
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (addedPages.find(page) != addedPages.end()) {
            continue;
        }
        vector<int> pageDependencies = dependencies[page];
        bool isValidPage = true;
        for (int j = 0; j < pageDependencies.size(); j++) {
            int dependency = pageDependencies[j];
            if (includedPages.find(dependency) == includedPages.end() ||
                addedPages.find(dependency) != addedPages.end()) {
                continue;
            }
            isValidPage = false;
            break;
        }
        if (isValidPage) {
            toReturn.push_back(page);
        }
    }
    return toReturn;
}

void fixUpdateHelper(vector<int> *output, std::map<int, vector<int>> dependencies, Update update,
                     vector<int> fixedPages, int page) {
    fixedPages.push_back(page);
    if (fixedPages.size() >= update.pages.size()) {
        // cout << "Reached end" << endl;
        for (int i = 0; i < fixedPages.size(); i++) {
            output->push_back(fixedPages[i]);
        }
        return;
    }

    // Make addedPages set
    std::set<int> addedPages;
    // cout << "\tCurrAddedPages: ";
    for (int i = 0; i < fixedPages.size(); i++) {
        addedPages.insert(fixedPages[i]);
        // cout << fixedPages[i] << ", ";
    }
    // cout << endl;
    vector<int> validPages = findValidPages(dependencies, update.includedPages, addedPages, update.pages);
    for (int i = 0; i < validPages.size(); i++) {
        fixUpdateHelper(output, dependencies, update, fixedPages, validPages[i]);
    }
}

vector<int> fixUpdate(std::map<int, vector<int>> dependencies, Update update) {
    std::set<int> addedPages;
    vector<int> validPages = findValidPages(dependencies, update.includedPages, addedPages, update.pages);
    // cout << "Valid starting pages : ";
    vector<int> output;
    for (int i = 0; i < validPages.size(); i++) {
        // cout << validPages[i] << ", ";
        fixUpdateHelper(&output, dependencies, update, vector<int>(), validPages[i]);
    }
    // cout << endl;

    // cout << "Fixed: ";
    for (int i = 0; i < output.size(); i++) {
        // cout << output[i] << ", ";
    }
    // cout << endl << endl;
    return output;
}

bool isUpdateValid(std::map<int, vector<int>> dependencies, const Update update) {
    std::set<int> addedPages;
    for (int i = 0; i < update.pages.size(); i++) {
        int page = update.pages[i];
        vector<int> pageDependencies = dependencies[page];
        for (int j = 0; j < pageDependencies.size(); j++) {
            // Dependency is included in update but doesn't exist in added pages
            if (update.includedPages.find(pageDependencies[j]) != update.includedPages.end() &&
                addedPages.find(pageDependencies[j]) == addedPages.end()) {
                return false;
            }
        }
        addedPages.insert(page);
    }
    return true;
}

void part1(std::map<int, vector<int>> dependencies, vector<Update> updates) {
    int toReturn = 0;
    for (int i = 0; i < updates.size(); i++) {
        if (isUpdateValid(dependencies, updates[i])) {
            int midIndex = updates[i].pages.size() / 2;
            toReturn += updates[i].pages[midIndex];
        }
    }
    cout << "Middle page number sum = " << toReturn << endl;
}

void part2(const std::map<int, vector<int>> &dependencies, const vector<Update> &updates) {
    int toReturn = 0;
    for (int i = 0; i < updates.size(); i++) {
        if (!isUpdateValid(dependencies, updates[i])) {
            cout << "Found invalid update! Fixing..." << endl;
            vector<int> fixedPages = fixUpdate(dependencies, updates[i]);
            cout << "\tFixed pages: [";
            for (int j = 0; j < fixedPages.size(); j++) {
                cout << fixedPages[j] << ", ";
            }
            cout << "]" << endl;

            int midIndex = fixedPages.size() / 2;
            toReturn += fixedPages[midIndex];
        }
    }
    cout << "Answer = " << toReturn << endl;
}

int main() {
    try {
        std::map<int, vector<int>> dependencies;
        vector<Update> updates;
        int updatesStartIndex = 0;

        vector<string> lines = readLines("input");

        for (int i = 0; i < lines.size(); i++) {
            if (lines[i] == "") {
                updatesStartIndex = i + 1;
                break;
            }
            vector<string> split = splitStr(lines[i], '|');
            int page = stoi(split[1]);
            int dependency = stoi(split[0]);
            dependencies[page].push_back(dependency);
        }

        for (int i = updatesStartIndex; i < lines.size(); i++) {
            Update toPush;
            std::set<int> includedPages;
            vector<int> pages;
            vector<string> split = splitStr(lines[i], ',');
            for (int j = 0; j < split.size(); j++) {
                int page = stoi(split[j]);
                pages.push_back(page);
                includedPages.insert(page);
            }
            toPush.includedPages = includedPages;
            toPush.pages = pages;
            updates.push_back(toPush);
        }

        part2(dependencies, updates);

    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
