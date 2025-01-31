#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct Robot {
    int x, y, vx, vy;
};

const int WIDTH = 101;
const int HEIGHT = 103;
const int TIME = 100;

vector<Robot> parseInput() {
    vector<Robot> robots;
    string line;
    while (getline(cin, line)) {
        Robot r;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &r.x, &r.y, &r.vx, &r.vy);
        robots.push_back(r);
    }
    return robots;
}

void updatePositions(vector<Robot>& robots) {
    for (Robot& r : robots) {
        r.x = (r.x + TIME * r.vx) % WIDTH;
        r.y = (r.y + TIME * r.vy) % HEIGHT;
        if (r.x < 0) r.x += WIDTH;
        if (r.y < 0) r.y += HEIGHT;
    }
}

int computeSafetyFactor(const vector<Robot>& robots) {
    map<pair<int, int>, int> grid;
    for (const Robot& r : robots) {
        grid[{r.x, r.y}]++;
    }

    int midX = WIDTH / 2, midY = HEIGHT / 2;
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    for (const auto& [pos, count] : grid) {
        int x = pos.first, y = pos.second;
        if (x == midX || y == midY) continue;  // Ignore middle line
        if (x < midX && y < midY)
            q1 += count;
        else if (x > midX && y < midY)
            q2 += count;
        else if (x < midX && y > midY)
            q3 += count;
        else if (x > midX && y > midY)
            q4 += count;
    }

    return q1 * q2 * q3 * q4;
}

int main() {
    vector<Robot> robots = parseInput();
    updatePositions(robots);
    int safetyFactor = computeSafetyFactor(robots);
    cout << "Safety Factor: " << safetyFactor << endl;
    return 0;
}
