#include <iostream>
#include <vector>
#include <algorithm> // for std::shuffle
#include <random>    // for std::default_random_engine
#include <ctime>     // for std::time

using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    // Check if a queen can be placed in this position
    for (int i = 0; i < col; ++i) {
        if (board[row][i]) {
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j]) {
            return false;
        }
    }

    for (int i = row, j = col; i < N && j >= 0; ++i, --j) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

bool solveNQueens(vector<vector<int>>& board, int col, int N) {
    // Base case: If all queens are placed, print the solution
    if (col >= N) {
        cout << "Solution found:" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << (board[i][j] ? "Q " : ". ");
            }
            cout << endl;
        }
        cout << endl;
        return true; // Indicate that a solution was found
    }

    // Try placing this queen in all rows one by one, but shuffle the order
    vector<int> row_indices(N);
    for (int i = 0; i < N; ++i) {
        row_indices[i] = i;
    }

    // Seed the random number generator with the current time
    unsigned seed = std::time(0);
    shuffle(row_indices.begin(), row_indices.end(), std::default_random_engine(seed));

    for (int i = 0; i < N; ++i) {
        int row = row_indices[i];
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1;  // Place the queen

            // Recur to place the rest of the queens
            if (solveNQueens(board, col + 1, N)) {
                return true; // Indicate that a solution was found
            }

            // If placing the queen in board[row][col] doesn't lead to a solution,
            // then remove the queen (backtrack)
            board[row][col] = 0;
        }
    }
    

    // If the queen can't be placed in any row of this column, return false
    return false;
}

int main() {
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;
    cout<<N<<endl;
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueens(board, 0, N)) {
        cout << "No solution found." << endl;
    }

    return 0;
}
