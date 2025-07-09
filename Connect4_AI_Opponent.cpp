#include <iostream>
#include <vector>
#include <string>
#include "GameBoard.cpp"
#include "AIPlayer.cpp"
#include "HumanPlayer.cpp"  
using namespace std;

int main() {

    cout << "Welcome Noob, uhm, I mean Human! Let's play Connect4!\n";
    cout << "Which difficulty level would you like to be defeated by? (easy / med / hard): ";

    string level;
    int depth = 4;
    cin >> level;

    if (level == "easy") {
        depth = 2;
        cout << "Starting on baby mode, are we?\n";
    } else if (level == "med") {
        depth = 4;
        cout << "Not bad. Let's see what you've got.\n";
    } else if (level == "hard") {
        depth = 6;
        cout << "You're going to regret this.\n";
    } else {
        cout << "Invalid input. I'll go with medium, gives you a tiny chance.\n";
        depth = 4;
    }

    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        GameBoard game;
        HumanPlayer player1(1);       
        AIPlayer ai(2, depth);            

        int currentPlayer = 1;

        cout << "\nAlright! The board is ready. You go first, Human.\n";
        game.printBoard();

        while (true) {
            int moveCol;

            if (currentPlayer == 1) {
                moveCol = player1.getMove(game);
            } else {
                moveCol = ai.getMove(game);
                cout << "I played into column " << moveCol << ". Your turn!\n";
            }

            game.dropPiece(moveCol, currentPlayer);
            game.printBoard();

            if (game.checkWin(currentPlayer)) {
                if (currentPlayer == 2) {
                    cout << "That's how it's done. I win.\n";
                    cout << "Practice and maybe try again later... or not.\n";
                } else {
                    cout << "You Win!\n";
                    cout << "Enjoy this once-in-a-lifetime victory.\n";
                }
                break;
            }

            if (game.isFull()) {
                cout << "Looks like it's a draw. Lucky you!\n";
                break;
            }

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }

        // Ask to play again
        while (true) {
            cout << "\nWant another beating? (y/n): ";
            cin >> playAgain;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Just say 'y' or 'n'.\n";
                continue;
            }

            cin.ignore(10000, '\n');

            if (playAgain == 'y' || playAgain == 'Y') {
                cout << "Back for more? Let's go again.\n";
                break;
            }
            if (playAgain == 'n' || playAgain == 'N') {
                cout << "Running away? Fine. Come back when you're braver.\n";
                return 0;
            }

            cout << "Please enter a valid choice (y/n).\n";
        }
    }

    return 0;
}
