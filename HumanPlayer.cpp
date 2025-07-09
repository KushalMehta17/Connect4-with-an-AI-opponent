#include <iostream>
using namespace std;

class HumanPlayer {
private:
    int playerId;

public:
    HumanPlayer(int id) {
        playerId = id;
    }

    int getMove(GameBoard& board) {
        int col;

        while (true) {
            cout << "Enter column (0-6): ";
            cin >> col;
            

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Enter a number between 0 and 6.\n";
                continue;
            }

            if (!board.isValidMove(col)) {
                cout << "Invalid move! This column is either full or out of range.\n";
                continue;
            }

            break; // valid move
        }

        return col;
    }
};
