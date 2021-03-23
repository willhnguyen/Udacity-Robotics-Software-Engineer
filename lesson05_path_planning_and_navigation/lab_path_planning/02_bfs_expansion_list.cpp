#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Map class
class Map {
public:
    const static int mapWidth = 6;
    const static int mapHeight = 5;
    vector<vector<int> > grid = {
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0 }
    };
};

// Planner class
class Planner : Map {
public:
    int start[2] = { 0, 0 };
    int goal[2] = { mapHeight - 1, mapWidth - 1 };
    int cost = 1;

    string movements_arrows[4] = { "^", "<", "v", ">" };

    vector<vector<int> > movements{
        { -1, 0 },
        { 0, -1 },
        { 1, 0 },
        { 0, 1 }
    };
};

// Template function to print 2D vectors of any type
template <typename T>
void print2DVector(T Vec)
{
    for (int i = 0; i < Vec.size(); ++i) {
        for (int j = 0; j < Vec[0].size(); ++j) {
            cout << Vec[i][j] << ' ';
        }
        cout << endl;
    }
}

/*#### TODO: Code the search function which will generate the expansion list ####*/
// You are only required to print the final triplet values
template <typename T>
class CompareVectors {
public:
    bool operator() (vector<T> &e1, vector<T> &e2) {
        size_t length = min(e1.size(), e2.size());

        for (size_t i = 0; i < length; ++i) {
            if (e1[i] == e2[i]) {
                continue;
            }

            return e1[i] > e2[i];
        }

        return false;
    }
};

template <typename T>
void printVector(vector<T> vec) {
    cout << '[';
    for (T &el : vec) {
        cout << el << ' ';
    }
    cout << ']';
}

template <typename T>
void printQueue(priority_queue<vector<T>, vector<vector<T> >, CompareVectors<T> > &pq) {
    vector<vector<T> > elements;

    // Print elements as we pop them
    while (!pq.empty()) {
        vector<T> current = pq.top();
        pq.pop();
        elements.push_back(current);
        
        printVector<T>(current);
    }

    // Put elements back
    for (vector<T> &el : elements) {
        pq.push(el);
    }
}


void search(Map map, Planner planner)
{
    vector<vector<int> > visited(map.mapWidth, vector<int>(map.mapHeight, 0));
    priority_queue<vector<int>, vector<vector<int> >, CompareVectors<int> > bfs_queue;

    // Start with cell (0, 0)
    int g = 0;
    int x = planner.start[0];
    int y = planner.start[1];

    vector<int> triplet = {g, x, y};
    visited[x][y] = 1;

    bfs_queue.push(triplet);

    int expansion_number = 0;

    while ( !bfs_queue.empty() && expansion_number < 25) {
        // cout << "Expansion #: " << expansion_number << endl;
        // cout << "Open List: ";
        // printQueue(bfs_queue);
        // cout << endl;

        triplet = bfs_queue.top();
        bfs_queue.pop();

        g = triplet[0];
        x = triplet[1];
        y = triplet[2];

        // cout << "Cell Picked: ";
        // printVector(triplet);
        // cout << endl << endl;

        // Check if goal is reached 
        // cout << "Is goal (" << planner.goal[0] << ", " << planner.goal[1] << ") reachable?" << endl;
        if (x == planner.goal[0] && y == planner.goal[1]) {
            // cout << "Goal is reached" << endl;
            cout << "[" << g << "," << x << "," << y << "]" << endl;
            break;
        }

        // cout << "Check all possible movements" << endl;
        for (int move_i = 0; move_i < planner.movements.size(); ++move_i) {
            int delta_x = planner.movements[move_i][0];
            int delta_y = planner.movements[move_i][1];

            int g_prime = g + planner.cost;
            int x_prime = x + delta_x;
            int y_prime = y + delta_y;

            // Check if next location is possible
            if (x_prime < 0 || x_prime >= map.mapHeight || y_prime < 0 || y_prime >= map.mapWidth) {  // Impossible movements
                continue;
            }
            else if (map.grid[x_prime][y_prime] == 1) {  // Obstacle in the way
                continue;
            }
            else if (visited[x_prime][y_prime] != 0) {  // Already in queue or has been visited
                continue;
            }

            // cout << "Moving: " << planner.movements_arrows[move_i] << endl;
            triplet = {g_prime, x_prime, y_prime};
            bfs_queue.push(triplet);
            visited[x_prime][y_prime] = 1;
        }
        ++expansion_number;
    }



}

int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Search for the expansions
    search(map, planner);

    return 0;
}
