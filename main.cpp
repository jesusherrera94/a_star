#include <iostream>
#include<vector>
#include <fstream>
#include <string>
using std::cout;
using std::vector;
using std::ifstream;
using std::string;

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