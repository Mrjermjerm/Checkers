
#include <iostream>
using namespace std;


const int SIZE = 8; // Checker Board 8 x 8

void intializeBoard(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++)  // i = Rows
    {
        for (int j = 0; j < SIZE; j++) // j = Coulmns
        {
            board[i][j] = ' '; // Start with all cells as empty
        }
    }

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


// Prints Board with Current Values
void printBoard(char board[SIZE][SIZE]) 
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

int selectSpaceToMove(char columnSelectChar, int columnSelectInt)
{
    
    if(columnSelectChar == 'A')         {columnSelectInt = 0;}
    else if(columnSelectChar == 'B')    {columnSelectInt = 1;}
    else if(columnSelectChar == 'C')    {columnSelectInt = 2;}
    else if(columnSelectChar == 'D')    {columnSelectInt = 3;}
    else if(columnSelectChar == 'E')    {columnSelectInt = 4;}
    else if(columnSelectChar == 'F')    {columnSelectInt = 5;}
    else if(columnSelectChar == 'G')    {columnSelectInt = 6;}
    else if(columnSelectChar == 'H')    {columnSelectInt = 7;}

    return columnSelectInt;
}

// To move a piece
void movePiece(char board[SIZE][SIZE]) 
{
    // Enter the desired piece to move
    cout << "Select Column (letters): ";   // Enter the Column
    char columnSelectChar;                 // Character for coulmn select A - H
    cin >> columnSelectChar;               // Chosen Character
    int columnSelectInt;                   // Column Index
    
    cout << "Select Row (numbers): ";      // Enter The Row
    int rowSelect; 
    cin >> rowSelect;

    // Changes Letters into numbers to fit the column index
    selectSpaceToMove(columnSelectChar,columnSelectInt);  


    // Enter the targeted position to move to
    cout << "Select space to move" << endl;
    cout << "Select Column (letters): ";    // Enter the column for new position
    char columnTargetChar;
    cin >> columnTargetChar;
    int columnTarget;

    cout << "Select Row (numbers): ";      // Enter The Row for new position
    int rowTarget; 
    cin >> rowTarget;
    
    // Changes Letters into numbers to fit the column index
    selectSpaceToMove(columnTargetChar, columnTarget);  

    for (int i = 0; i < SIZE; i++)  // i = Rows
    {
        for (int j = 0; j < SIZE; j++) // j = Coulmns
        {
            if (board[rowSelect][selectSpaceToMove(columnSelectChar, columnSelectInt)] == board[i][j] && board[i][j] != ' ')
            {
                // Piece is moved to new position
                board[rowTarget][selectSpaceToMove(columnTargetChar, columnTarget)] = board[rowSelect][selectSpaceToMove(columnSelectChar, columnSelectInt)];
                board[rowSelect][selectSpaceToMove(columnSelectChar, columnSelectInt)] = ' '; 
            }
        }
    }
}



int main()
{
    char board[SIZE][SIZE]; // Create Board
    intializeBoard(board); // Call intializeBoard to start
    

    printBoard(board); // Print Board with current values

    movePiece(board); // Move Piece

    printBoard(board);
}