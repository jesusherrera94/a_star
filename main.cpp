#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>  // for sort

using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::sort;

// Enum for obstacle and empty cell
enum class State {kEmpty, kObstacle, kClosed, kPath};

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

vector<State> ParseLine (string line) {
  	vector<State> fetched_board_line {};
  	istringstream line_stream(line);
	int element;
  	char token;
  	while (line_stream >> element >> token && token == ',') {
    	fetched_board_line.push_back(element == 0 ? State::kEmpty : State::kObstacle);
    }
  	return fetched_board_line;
}


vector<vector<State>> ReadBoardFile(string path) {
	ifstream board_file;
  	board_file.open(path);
  	vector<vector<State>> board {};
  if (board_file) {
  	cout<<"The file has been opened successfully! \n";
    string line;
    while (getline(board_file, line)) {
      board.push_back(ParseLine(line));
    }
  }
  return board;
}

bool Compare(const vector<int> a, const vector<int> b) {
  int f1 = a[2] + a[3]; // f1 = g1 + h1
  int f2 = b[2] + b[3]; // f2 = g2 + h2
  return f1 > f2; 
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

int Heuristic (int x1, int y1, int x2, int y2) {
	return std::abs(x2 - x1) + std::abs(y2 - y1);
}

bool CheckValidCell (int x, int y, vector<vector<State>> &grid) {
	int rowSize = grid.size();
  	int columSize = grid[0].size();
  	if ((x < 0 || x > (rowSize - 1)) 
        || (y < 0 || y > (columSize - 1))) {
      	// cout<<"Invalid coordinate!: ("<<x<<", "<<y<<") \n";
    	return false;
    }
   return grid[x][y] == State::kEmpty;
}

void AddToOpen (int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid) {
	vector<int> node {x, y, g, h};
  	open_nodes.push_back(node);
  	grid[x][y] = State::kClosed;
}

void ExpandNeighbors(auto &current_node, const int goal[2], auto &open, vector<vector<State>> &grid) {
  
  int x = current_node[0];
  int y = current_node[1];
  int g = current_node[2];
  std::size_t deltaSize = sizeof(delta) / sizeof(delta[0]);

  for (int i = 0; i < deltaSize; i++) {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];
    
    if (CheckValidCell(x2, y2, grid)) {
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, open, grid);
    }
  }
}

vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
  // Create the vector of open nodes.
  vector<vector<int>> open {};
  
  // Initialize the starting node.
  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0],goal[1]);
  AddToOpen(x, y, g, h, open, grid);
 while (!open.empty()) {
 	CellSort(&open);
   auto current = open.back();
    open.pop_back();
   cout<<current[0]<<", "<<current[1]<<", "<<current[2]<<", "<<current[3]<<", \n";
    x = current[0];
    y = current[1];
    grid[x][y] = State::kPath;
    if (x == goal[0] && y == goal[1]) {
      return grid;
    }
   
       // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
    ExpandNeighbors(current, goal, open, grid);
 }
  
  // We've run out of new nodes to explore and haven't found a path.
  cout << "No path found!" << "\n";
  return std::vector<vector<State>>{};
}

// function to print the formatted cell string
string CellString (State cell) {
	if (cell == State::kObstacle) {
    	return "⛰️   ";
    }
  if (cell == State::kPath) {
    return "🚗   ";
  }
  	return "0   ";
}

void PrintBoard(vector<vector<State>> board) {
	for(auto row : board) {
    	for(State col : row) {
			// static cast is for converting the int to State enum
        	// cout<<CellString(static_cast<State>(col));
			cout<<CellString(col);
        }
      	cout<<"\n";
    }
}

int main() {
   vector<vector<State>> board {};
   int init[2]{0, 0};
   int goal[2]{4, 5};
   board = ReadBoardFile("1.board");
   auto solution = Search(board, init, goal);
  PrintBoard(solution);
}