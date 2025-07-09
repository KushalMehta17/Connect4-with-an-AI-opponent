#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class AIPlayer {
private:
    int playerId;
    int opponentId;
    int maxDepth;

public:
    AIPlayer(int id, int depth) {
        playerId = id;
        opponentId = (id == 1) ? 2 : 1;
        maxDepth = depth;
    }

    // Get best column using minimax
    int getMove(GameBoard& board) {
        int bestScore = INT_MIN;
        int bestCol = 0;

        for (int col = 0; col < 7; col++) {
            if (board.isValidMove(col)) {
                board.simulateMove(col, playerId);
                int score = minimax(board, maxDepth - 1, false, INT_MIN, INT_MAX);
                board.undoMove(col);

                if (score > bestScore) {
                    bestScore = score;
                    bestCol = col;
                }
            }
        }
        return bestCol;
    }

    // Minimax recursive search
    int minimax(GameBoard& board, int depth, bool maximizingPlayer, int alpha, int beta) {
        if (board.checkWin(playerId)) return 100000;
        if (board.checkWin(opponentId)) return -100000;
        if (depth == 0 || board.isFull()) return evaluateBoard(board);


        if (maximizingPlayer) {
            int maxEval = INT_MIN;

            for (int col = 0; col < 7; col++) {
                if (board.isValidMove(col)) {
                    board.simulateMove(col, playerId);
                    int eval = minimax(board, depth - 1, false, alpha, beta);
                    board.undoMove(col);

                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);

                    if (alpha >= beta) break;
                }
            }
            return maxEval;
        } else {
            int minEval = INT_MAX;

            for (int col = 0; col < 7; col++) {
                if (board.isValidMove(col)) {
                    board.simulateMove(col, opponentId);
                    int eval = minimax(board, depth - 1, true, alpha, beta);
                    board.undoMove(col);

                    minEval = min(minEval, eval);
                    beta = min(beta, eval);

                    if (beta <= alpha) break;
                }
            }
            return minEval;
        }
    }

    int evaluateLine(const vector<int>& window) {
        int myCount = 0, oppCount = 0, empty = 0;

        for (int val : window) {
            if (val == playerId) myCount++;
            else if (val == opponentId) oppCount++;
            else empty++;
        }

        int score = 0;
        if (myCount == 4) score += 100000;
        else if (myCount == 3 && empty == 1) score += 500;
        else if (myCount == 2 && empty == 2) score += 50;

        if (oppCount == 4) score -= 100000; 
        else if (oppCount == 3 && empty == 1) score -= 700;
        else if (oppCount == 2 && empty == 2) score -= 30;

        return score;
    }

    int evaluateBoard(GameBoard& board) {
        int score = 0;
        vector<vector<int>> grid = board.getRawBoard();

        // Score center column preference
        for (int r = 0; r < 6; r++) {
            if (grid[r][3] == playerId)
                score += 3;  // Encourage center column
        }

        // Check horizontal lines
        for (int r = 0; r < 6; r++) {
            for (int c = 0; c < 4; c++) {
                vector<int> window = {grid[r][c], grid[r][c+1], grid[r][c+2], grid[r][c+3]};
                score += evaluateLine(window);
            }
        }

        // Check vertical lines
        for (int c = 0; c < 7; c++) {
            for (int r = 0; r < 3; r++) {
                vector<int> window = {grid[r][c], grid[r+1][c], grid[r+2][c], grid[r+3][c]};
                score += evaluateLine(window);
            }
        }

        // Positive diagonals (/)
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 4; c++) {
                vector<int> window = {grid[r][c], grid[r+1][c+1], grid[r+2][c+2], grid[r+3][c+3]};
                score += evaluateLine(window);
            }
        }

        // Negative diagonals (\)
        for (int r = 3; r < 6; r++) {
            for (int c = 0; c < 4; c++) {
                vector<int> window = {grid[r][c], grid[r-1][c+1], grid[r-2][c+2], grid[r-3][c+3]};
                score += evaluateLine(window);
            }
        }

        return score;
    }

};
