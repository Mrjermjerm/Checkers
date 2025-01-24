//
//  main.cpp
//  Sprint 1 - Checkers
//
//  Created by Bryce Langford on 1/17/25.
//

#include <iostream>
using namespace std;

const int SIZE = 8; // Checker Board 8 x 8

bool isValidMove(char board[SIZE][SIZE], int fromRow, int fromCol, int toRow, int toCol, char player);
void makeMove(char board[SIZE][SIZE], int fromRow, int fromCol, int toRow, int toCol);
bool canCapture(char board[SIZE][SIZE], int row, int col, char player);

void displayTitleScreen() {
    cout << R"(
  ▄████▄   ██░ ██ ▓█████  ▄████▄   ██ ▄█▀▓█████  ██▀███    ██████ 
 ▒██▀ ▀█  ▓██░ ██▒▓█   ▀ ▒██▀ ▀█   ██▄█▒ ▓█   ▀ ▓██ ▒ ██▒▒██    ▒ 
 ▒▓█    ▄ ▒██▀▀██░▒███   ▒▓█    ▄ ▓███▄░ ▒███   ▓██ ░▄█ ▒░ ▓██▄   
 ▒▓▓▄ ▄██▒░▓█ ░██ ▒▓█  ▄ ▒▓▓▄ ▄██▒▓██ █▄ ▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒
 ▒ ▓███▀ ░░▓█▒░██▓░▒████▒▒ ▓███▀ ░▒██▒ █▄░▒████▒░██▓ ▒██▒▒██████▒▒
 ░ ░▒ ▒  ░ ▒ ░░▒░▒░░ ▒░ ░░ ░▒ ▒  ░▒ ▒▒ ▓▒░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░
   ░  ▒    ▒ ░▒░ ░ ░ ░  ░  ░  ▒   ░ ░▒ ▒░ ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░
 ░         ░  ░░ ░   ░   ░        ░ ░░ ░    ░     ░░   ░ ░  ░  ░  
 ░ ░       ░  ░  ░   ░  ░░ ░      ░  ░      ░  ░   ░           ░  
 ░                       ░                                          

                    『 STRATEGIC BOARD BATTLES 』
                      Press Enter to Begin)" << endl;
    
    cin.clear(); // Clear input buffer
    cin.ignore();
}

void initializeBoard(char board[SIZE][SIZE]) // Jeremy Sanders
{
    for (int i = 0; i < SIZE; i++)  // i = Rows
    {
        for (int j = 0; j < SIZE; j++) // j = Coulmns
        {
            board[i][j] = ' '; // Start with all cells as empty

            // Player X
           board[0][1] = 'X'; // Top Row
           board[0][3] = 'X';
           board[0][5] = 'X';
           board[0][7] = 'X';

           board[1][0] = 'X'; // Middle Row
           board[1][2] = 'X';
           board[1][4] = 'X';
           board[1][6] = 'X';

           board[2][1] = 'X'; // Bottom Row
           board[2][3] = 'X';
           board[2][5] = 'X';
           board[2][7] = 'X';

           //board[3][4] = 'A'; // Archerer (test piece)
           
           // Player O
           board[7][0] = 'O'; // Bottom Row
           board[7][2] = 'O';
           board[7][4] = 'O';
           board[7][6] = 'O';

           board[6][1] = 'O'; // Middle Row
           board[6][3] = 'O';
           board[6][5] = 'O';
           board[6][7] = 'O';

           board[5][0] = 'O'; // Top Row
           board[5][2] = 'O';
           board[5][4] = 'O';
           board[5][6] = 'O';
            
        }
    }
}


void printBoard(char board[SIZE][SIZE]) // Prints Board with Current Values by Jeremy Sanders
{
    cout << endl; // Space Above Board
    cout << "    A    B    C    D    E    F    G    H " << endl; // Coulmn Index for Board
    cout << "  |----|----|----|----|----|----|----|----|\n";
    for (int i = 0; i < SIZE; i++)
    {
        cout << i << " | "; // Prints Row Index followed By Spacing for Board
        for (int j = 0; j < SIZE; j++)
        {
            cout << board[i][j];
            if (j < SIZE -1) cout << "  | "; // Vertical Seperator
        }
        cout << endl; // Next Row
        if (i < SIZE -1) cout << "  |----|----|----|----|----|----|----|----|\n";
    }
    cout << "  |----|----|----|----|----|----|----|----|";
    cout << endl; // Space After Board
}

bool isValidMove(char board[SIZE][SIZE], int fromRow, int fromCol, int toRow, int toCol, char player) {
    // Check if destination is empty
    if (board[toRow][toCol] != ' ') return false;
    
    // Check if destination is on a diagonal
    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;
    
    // Basic move: one square diagonally
    if (abs(rowDiff) == 1 && abs(colDiff) == 1) {
        // X moves down, O moves up
        if (player == 'X' && rowDiff > 0) return true;
        if (player == 'O' && rowDiff < 0) return true;
    }
    
    // Capture move: two squares diagonally
    if (abs(rowDiff) == 2 && abs(colDiff) == 2) {
        int jumpRow = fromRow + rowDiff/2;
        int jumpCol = fromCol + colDiff/2;
        char opponent = (player == 'X') ? 'O' : 'X';
        
        // Check if there's an opponent's piece to capture
        if (board[jumpRow][jumpCol] == opponent) {
            return true;
        }
    }
    
    return false;
}

void makeMove(char board[SIZE][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    // Move the piece
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = ' ';
    
    // If it was a capture move, remove the captured piece
    if (abs(toRow - fromRow) == 2) {
        int jumpRow = (fromRow + toRow) / 2;
        int jumpCol = (fromCol + toCol) / 2;
        board[jumpRow][jumpCol] = ' ';
    }
}

bool canCapture(char board[SIZE][SIZE], int row, int col, char player) {
    // Check all possible capture directions
    int directions[4][2] = {{2,2}, {2,-2}, {-2,2}, {-2,-2}};
    
    for (int i = 0; i < 4; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        
        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
            if (isValidMove(board, row, col, newRow, newCol, player)) {
                return true;
            }
        }
    }
    return false;
}




int main()
{
    char board[SIZE][SIZE]; // Create Board
    char currentPlayer = 'X';
    bool gameOver = false;
    
    displayTitleScreen(); // Add this line to show the title screen
    initializeBoard(board); // Call intializeBoard to start

    while (!gameOver) {
            printBoard(board);
            
            cout << "Player " << currentPlayer << "'s turn\n";
            
            // Get move input
            char fromCol, toCol;
            int fromRow, toRow;
            
            // cout << "Enter move (e.g., B2 C3): ";
            // cin >> fromCol >> fromRow >> toCol >> toRow;
            cout << "Move from (B3): ";
            cin >> fromCol >> fromRow;
            cout << "Move to (C4): ";
            cin >> toCol >> toRow;
            
            // Convert input to array indices
            int fromColIdx = toupper(fromCol) - 'A';
            int toColIdx = toupper(toCol) - 'A';
            
            if (isValidMove(board, fromRow, fromColIdx, toRow, toColIdx, currentPlayer)) {
                makeMove(board, fromRow, fromColIdx, toRow, toColIdx);
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            } else {
                cout << "Invalid move! Press Enter to try again.";
                cin.ignore();
                cin.get();
            }
            
            // future win-condition-check here
        }
        
        return 0;
    }
