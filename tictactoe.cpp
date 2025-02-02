#include <iostream>
using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char currentMarker;
int currentPlayer;

void clearConsole() {
   
    system("clear"); 

}

void drawBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Display colored markers
            if (board[i][j] == 'X') {
                cout << "\033[31mX\033[0m"; // Red for X
            } else if (board[i][j] == 'O') {
                cout << "\033[34mO\033[0m"; // Blue for O
            } else {
                cout << board[i][j];
            }
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---------\n";
    }
    cout << "\n";
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;
        return true;
    } else {
        return false;
    }
}

int winner() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return currentPlayer;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return currentPlayer;
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return currentPlayer;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return currentPlayer;

    return 0;
}

void swapPlayerAndMarker() {
    if (currentMarker == 'X') {
        currentMarker = 'O';
        currentPlayer = 2;
    } else {
        currentMarker = 'X';
        currentPlayer = 1;
    }
}

void game() {
    cout << "Player 1, choose your marker (X or O): ";
    char markerP1;

    do {
        cin >> markerP1;
        if (markerP1 != 'X' && markerP1 != 'O') {
            cout << "Invalid marker! Please choose 'X' or 'O'.\n";
        }
    } while (markerP1 != 'X' && markerP1 != 'O');

    currentMarker = markerP1;
    currentPlayer = 1;

    int winnerPlayer = 0;

    for (int i = 0; i < 9; i++) {
        cout << "Player " << currentPlayer << "'s turn (" << currentMarker << ")\n";
        clearConsole(); // Clear the console
        drawBoard(); // Display the board

        cout << "Enter your slot: ";
        int slot;
        cin >> slot;

        if (slot < 1 || slot > 9) {
            cout << "Invalid slot! Choose a slot between 1 and 9.\n";
            i--;
            continue;
        }

        if (!placeMarker(slot)) {
            cout << "Slot already taken! Try again.\n";
            i--;
            continue;
        }

        winnerPlayer = winner();
        if (winnerPlayer != 0) {
            clearConsole();
            cout << "Player " << winnerPlayer << " wins!\n";
            drawBoard();
            return;
        }

        swapPlayerAndMarker();
    }

    clearConsole();
    drawBoard();
    cout << "It's a tie!\n";
}

int main() {
    cout << "Welcome to Tic Tac Toe!\n";
    game();
    return 0;
}
