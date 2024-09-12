#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

// Enum for obstacle and empty cell
enum class State {kEmpty, kObstacle, kClosed};

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

// function to print the formatted cell string
string CellString (State cell) {
	if (cell == State::kObstacle) {
    	return "⛰️   ";
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

int Heuristic (int x1, int y1, int x2, int y2) {
	return std::abs(x2 - x1) + std::abs(y2 - y1);
}

void AddToOpen (int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid) {
	vector<int> node {x, y, g, h};
  	open_nodes.push_back(node);
  	grid[x][y] = State::kClosed;
}

vector<vector<State>> Search(vector<vector<State>> board, int init[2], int goal[2]) {
  	vector<vector<int>> open {};
 	int x = init[0];
  	int y = init[1];
  	int g = 0;
  	int h = Heuristic(x,y, goal[0], goal[1]);
	AddToOpen(x,y,g,h,open,board);
  	cout << "No path found!" << "\n";
  	return {};
}

int main() {
   vector<vector<State>> board {};
   int init[2]{0, 0};
   int goal[2]{4, 5};
   board = ReadBoardFile("1.board");
   auto solution = Search(board, init, goal);
  PrintBoard(solution);
}