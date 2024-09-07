#include <iostream>
#include<vector>
using std::cout;
using std::vector;

void PrintBoard(vector<vector<int>> board) {
	for(auto row : board) {
    	for(int col : row) {
        	cout<<col;
        }
      	cout<<"\n";
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
  PrintBoard(board);
  cout << "Hello!" << "\n";
}