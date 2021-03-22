#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

/* TODO: Define a Map class
   Inside the map class, define the mapWidth, mapHeight and grid as a 2D vector
*/
class Map {
public:
  Map() {
    mapWidth = 6;
    mapHeight = 5;
    
    grid = {
      {0, 1, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 0}
    };
  }
  
  int mapWidth;
  int mapHeight;
  vector<vector<int> > grid;
};

/* TODO: Define a Planner class
   Inside the Planner class, define the start, goal, cost, movements, and movements_arrows
   Note: The goal should be defined it terms of the mapWidth and mapHeight
*/
class Planner {
public:
  Planner() {
      start = {0, 0};
      goal = {4, 5};
      
      cost = 1;
      movements = {
          {-1, 0},
          { 0,-1},
          { 1, 0},
          { 0, 1}
      };
      movements_arrows = {
          '^',
          '<',
          'v',
          '>'
      };
  }
  
  vector<int> start;
  vector<int> goal;
  int cost;
  vector<vector<int> > movements;
  vector<char> movements_arrows;
};

/* TODO: Define a print2DVector function which will print 2D vectors of any data type
   Example
   
   Input: 
   vector<vector<int> > a{{ 1, 0 },{ 0, 1 }};
   print2DVector(a);
   vector<vector<string> > b{{ "a", "b" },{ "c", "d" }};
   print2DVector(b);
   
   Output:
   1 0
   0 1
   a b
   c d
   Hint: You need to use templates
*/
template <typename T>
void print2DVector(vector<vector<T> > grid) {
    for (vector<T> &row : grid) {
        for (T &c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
}

/*############ Don't modify the main function############*/
int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Print classes variables
    cout << "Map:" << endl;
    print2DVector(map.grid);
    cout << "Start: " << planner.start[0] << " , " << planner.start[1] << endl;
    cout << "Goal: " << planner.goal[0] << " , " << planner.goal[1] << endl;
    cout << "Cost: " << planner.cost << endl;
    cout << "Robot Movements: " << planner.movements_arrows[0] << " , " << planner.movements_arrows[1] << " , " << planner.movements_arrows[2] << " , " << planner.movements_arrows[3] << endl;
    cout << "Delta:" << endl;
    print2DVector(planner.movements);

    return 0;
}
