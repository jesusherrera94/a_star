#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

// Enum for obstacle and empty cell
enum class State {kEmpty, kObstacle};

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

vector<vector<State>> Search(vector<vector<State>> board, int start[2], int goal[2]) {
	cout<<"No path found!"<<"\n";
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