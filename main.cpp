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

vector<int> ParseLine (string line) {
  	vector<int> fetched_board_line {};
  	istringstream line_stream(line);
	int element;
  	char token;
  	while (line_stream >> element >> token && token == ',') {
    	fetched_board_line.push_back(element);
    }
  	return fetched_board_line;
}

// TODO: Change the return type of ReadBoardFile.
vector<vector<int>> ReadBoardFile(string path) {
	ifstream board_file;
  	board_file.open(path);
  	vector<vector<int>> board {};
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

void PrintBoard(vector<vector<int>> board) {
	for(auto row : board) {
    	for(int col : row) {
			// static cast is for converting the int to State enum
        	cout<<CellString(static_cast<State>(col));
        }
      	cout<<"\n";
    }
}

int main() {
   vector<vector<int>> board {};
   board = ReadBoardFile("1.board");
   PrintBoard(board);
}