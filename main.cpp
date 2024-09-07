#include <iostream>
#include<vector>
#include <fstream>
#include <string>
#include <sstream>
using std::cout;
using std::vector;
using std::ifstream;
using std::string;
using std::istringstream;

vector<int> ParseLine (string line) {
  	vector<int> fetched_board_line {};
  	istringstream line_stream(line);
	int element;
  	char token;
  	while (line_stream >> element >> token) {
    	fetched_board_line.push_back(element);
    }
  	return fetched_board_line;
}

void PrintBoard(vector<vector<int>> board) {
	for(auto row : board) {
    	for(int col : row) {
        	cout<<col;
        }
      	cout<<"\n";
    }
}

void ReadBoardFile(string path) {
	ifstream board_file;
  board_file.open(path);
  if (board_file) {
  	cout<<"The file has been opened successfully! \n";
    string line;
    while (getline(board_file, line)) {
      cout<<line<<"\n";
    }
  }
}

int main() {
  // TODO: Declare a "board" variable here, and store
  // the data provided above.
  vector<vector<int>> board {{0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 0, 0, 0, 1, 0}};
  string file_path {"1.board"};
  ReadBoardFile(file_path);
  PrintBoard(board);
  cout << "Hello!" << "\n";
}