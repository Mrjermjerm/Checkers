
#include <iostream>
#include <limits>
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




// Convert Column letters into index
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



// Switch Players
bool switchplayer(bool player)
{
    if (player == true)
    {
        player = false;
        return player; // Player O
    }
    else
    {
        player = true;
        return player;  // Player X
    }
}




// To move a piece
void movePiece(char board[SIZE][SIZE], bool player, bool &dontSwitch) 
{
    if (player == true)
    {
        cout << "Player X" << endl;
    }
    else
    {
        cout << "Player O" << endl;
    }
    
    // Enter the desired piece to move
    cout << "Select Column (letters): ";   // Enter the Column
    char columnSelectChar;                 // Character for coulmn select A - H
    
    while(true)                            // Check for correct input
    {
        cin >> columnSelectChar;           // Chosen Column

        if (cin.fail() || cin.peek() != '\n')           
        {
            // Clear the error flag
            cin.clear();

            // Ignore remaining characters in the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input! Please enter a single character: ";
        }
        else if (isdigit(columnSelectChar))
        {
            // If the input is not an integer, handle the error
            cout << "Invalid input! That's not an integer." << endl;
            
            // Clear the error flag and ignore the invalid input
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the remaining invalid input
        }
        else
        {
            // Correct Input
            break;
        }
    }
    
    int columnSelectInt;                   // Column Index replaced by columnSelectChar
    
    cout << "Select Row (numbers): ";      // Enter The Row
    int rowSelect; 
    cin >> rowSelect;

    // Changes Letters into numbers to fit the column index
    columnSelectInt = selectSpaceToMove(columnSelectChar, 0);  

    // Check if the selected piece belongs to the correct player
    char playerSymbol = player ? 'X' : 'O';
    char opponentSymbol = player ? 'O' : 'X';

    // Check if the selected piece belongs to the correct player
    if ((player == true && board[rowSelect][columnSelectInt] != 'X') ||
        (player == false && board[rowSelect][columnSelectInt] != 'O'))
    {
        cout << "Selected wrong piece" << endl;
        dontSwitch = true;
        return; // Exit immediately
    }

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
    columnTarget = selectSpaceToMove(columnTargetChar, 0);

    // Diagonal Movement
    int rowDiff = rowTarget - rowSelect;
    int colDiff = columnTarget - columnSelectInt; 
    
    if (abs(rowDiff) != abs(colDiff)) // Must be a diagonal move
    {
        cout << "Invalid move! Pieces must move diagonally.\n";
        dontSwitch = true;
        return;
    }

    // Ensure the piece moves in the correct direction
    if ((player && rowDiff != 1) || (!player && rowDiff != -1)) 
    {
        cout << "Invalid move! You can only move forward.\n";
        dontSwitch = true;
        return;
    }

    // Ensure the target space is empty
    if (board[rowTarget][columnTarget] != ' ')
    {
        cout << "Invalid move! Target space is occupied.\n";
        dontSwitch = true;
        return;
    }

    // Capture logic (jumping over an opponent)
    if (abs(rowDiff) == 2) 
    {
        int jumpedRow = (rowSelect + rowTarget) / 2;
        int jumpedCol = (columnSelectInt + columnTarget) / 2;

        if (board[jumpedRow][jumpedCol] == opponentSymbol) 
        {
            board[jumpedRow][jumpedCol] = ' '; // Remove captured piece
        }
        else 
        {
            cout << "Invalid jump! No opponent piece to capture.\n";
            dontSwitch = true;
            return;
        }
    }
    
    // Move the piece
    board[rowTarget][columnTarget] = board[rowSelect][columnSelectInt];
    board[rowSelect][columnSelectInt] = ' ';
}




// Check Winner
int checkWinner(char board[SIZE][SIZE], int game)
{
    int countX = 0;
    int countO = 0;
    
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            if (board[i][j] == 'X')
            {
                countX++;
            }
            if (board[i][j] == 'O')
            {
                countO++;
            } 
        }
    } 

    if (countO == 0)
    {
        cout << "Congratulations to player X!" << endl;
        return 1;
    }
    if (countX == 0)
    { 
        cout << "Congratulations to player O!" << endl;
        return 1;
    }

    return 0;
}





// Main
int main()
{
    char board[SIZE][SIZE]; // Create Board
    intializeBoard(board); // Call intializeBoard to start
    

    printBoard(board); // Print Board with current values
    

    int game = 0;
    bool player = true;

    while (game == 0)
    {
        bool dontSwitch = false;
        
        movePiece(board, player, dontSwitch); // Move Piece

        printBoard(board);

        game = checkWinner(board, game);

        if (game == 0 && dontSwitch == false)
        {
            // Switch player
            player = switchplayer(player);
        }
    }
}