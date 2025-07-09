#include <iostream>
#include <vector>
using namespace std;

class GameBoard {
private:
    static const int ROWS = 6;
    static const int COLS = 7;
    vector<vector<int>> board;

public:
    GameBoard() {
        board = vector<vector<int>>(ROWS, vector<int>(COLS, 0));
    }

    void printBoard() {
        cout << "\n 0 1 2 3 4 5 6\n";
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                cout << "|";
                if (board[row][col] == 0) cout << " ";
                else if (board[row][col] == 1) cout << "X";
                else cout << "O";
            }
            cout << "|\n";
        }
        cout << "---------------------\n";
    }

    void loadBoard(const vector<vector<int>>& newBoard) {
        board = newBoard;
    }

    bool isValidMove(int col) {
        if (col < 0 || col >= COLS) return false;
        return board[0][col] == 0;
    }

    bool dropPiece(int col, int player) {
        if (!isValidMove(col)) return false;

        for (int row = ROWS - 1; row >= 0; row--) {
            if (board[row][col] == 0) {
                board[row][col] = player;
                return true;
            }
        }
        return false;
    }

    bool checkWin(int player) {
        // Horizontal check
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col <= COLS - 4; ++col) {
                if (board[row][col] == player &&
                    board[row][col+1] == player &&
                    board[row][col+2] == player &&
                    board[row][col+3] == player) {
                    return true;
                }
            }
        }

        // Vertical check
        for (int col = 0; col < COLS; ++col) {
            for (int row = 0; row <= ROWS - 4; ++row) {
                if (board[row][col] == player &&
                    board[row+1][col] == player &&
                    board[row+2][col] == player &&
                    board[row+3][col] == player) {
                    return true;
                }
            }
        }

        // Diagonal (bottom-left to top-right)
        for (int row = 3; row < ROWS; ++row) {
            for (int col = 0; col <= COLS - 4; ++col) {
                if (board[row][col] == player &&
                    board[row-1][col+1] == player &&
                    board[row-2][col+2] == player &&
                    board[row-3][col+3] == player) {
                    return true;
                }
            }
        }

        // Diagonal (top-left to bottom-right)
        for (int row = 0; row <= ROWS - 4; ++row) {
            for (int col = 0; col <= COLS - 4; ++col) {
                if (board[row][col] == player &&
                    board[row+1][col+1] == player &&
                    board[row+2][col+2] == player &&
                    board[row+3][col+3] == player) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isFull() {
        for (int col = 0; col < COLS; col++) {
            if (board[0][col] == 0) return false;
        }
        return true;
    }

    vector<vector<int>> getRawBoard() const {
        return board;
    }

    bool undoMove(int col) {
        for (int row = 0; row < ROWS; row++) {
            if (board[row][col] != 0) {
                board[row][col] = 0;
                return true;
            }
        }
        return false;
    }

    bool simulateMove(int col, int player) {
        for (int row = ROWS - 1; row >= 0; row--) {
            if (board[row][col] == 0) {
                board[row][col] = player;
                return true;
            }
        }
        return false;
    }
};