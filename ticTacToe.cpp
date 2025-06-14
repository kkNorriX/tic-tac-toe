//
//  ticTacToe.cpp
//  ticTicToe
//
//  Created by 肖旋 on 2024/4/4.
//

#include <iostream>
#include "ticTacToe.hpp"
#include "testCases.hpp"
#include "gameModes.hpp"

using namespace std;

int pieces[NUMPIECES];
int board[BOARDSIZE][BOARDSIZE];

int turn = 0;

/*--------------------------------------------------------------------------------------------------
 Local Function Declarations
--------------------------------------------------------------------------------------------------*/

char getMarker(int row, int col) {
    //Returns the character of the marker at location square
    return MARKERS[board[row][col]];
}

void printXpieces() {
    //Fancy print of X's remaining pieces
    cout << "x-pieces: { ";
    for (int i = 0; i < NUMPIECES/2; i++) {
        if (pieces[2*i] > 0) {
            cout << pieces[2*i] << MARKERS[2*i] << " ";
        }
    }
    cout << "}\n";
}

void printOpieces() {
    //Fancy print of O's remaining pieces
    cout << "O-pieces: { ";
    for (int i = 0; i < NUMPIECES/2; i++) {
        if (pieces[2*i+1] > 0) {
            cout << pieces[2*i+1] << MARKERS[2*i+1] << " ";
        }
    }
    cout << "}\n";
}

bool isLegalMove(int row, int col, int piece) {
    //Returns true if placing piece at row/col is legal, false otherwise
    if(piece == X_L || piece == O_L){
        if(board[row][col] == X_L || board[row][col] == O_L)
            return false;
        else
            return true;
    }else if(piece == X_M || piece == O_M){
        if(board[row][col] == X_S || board[row][col] == O_S || board[row][col] == EMPTY)
            return true;
        else
            return false;
    }else{
        if(board[row][col] == EMPTY)
            return true;
        else
            return false;
    }
}

void newGame() {
    // resets the board to empty and the number of pieces to 2 each
    turn = 0;
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            board[i][j] = 6;
        }
    }
    for (int i = 0; i < NUMPIECES; ++i) {
        pieces[i] = NUMPERPIECE;
    }
}

void printBoard() {
    // prints the board for the user to see
    printXpieces();
    printOpieces();

    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            cout << " ";
            if (j != 0) {
                cout << " | ";
            }
            cout << getMarker(i, j);
        }
        if (i != BOARDSIZE - 1) {
            cout << endl << " ---+----+---" << endl;
        }
    }
    cout << endl;
}

void printBoardMap() {
    // prints the map of the board
    cout << "    1 | 2 | 3" << endl;
    cout << "   ---+---+---" << endl;
    cout << "    4 | 5 | 6" << endl;
    cout << "   ---+---+---" << endl;
    cout << "    7 | 8 | 9" << endl;
}

int getLocation(int square) {
    // returns the piece (X_S, O_S...) or EMPTY for a given spot
    int row = (square - 1) / BOARDSIZE;
    int col = (square - 1) % BOARDSIZE;
    return board[row][col];
}

int markerToPiece(char piece) {
    // returns the piece number from the charecter; ILLEGAL if it is invalid
    // for instante 'x' would return X_S
    switch (piece) {
        case 'x':
            return X_S;
        case 'o':
            return O_S;
        case 'X':
            return X_M;
        case 'O':
            return O_M;
        case '#':
            return X_L;
        case '@':
            return O_L;
        default:
            return ILLEGAL;
    }
}

int getBoard(int board[BOARDSIZE][BOARDSIZE]) {
    // return a link to the board location
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            board[i][j] = ::board[i][j];
        }
    }
    return **board;
}

int takeTurn(int square, int piece) {
    if (pieces[piece] == 0) {
        cout << "No more pieces left for this marker." << endl;
        return ILLEGAL;
    }

    if (turn % 2 == 0 && !(piece == X_S || piece == X_M || piece == X_L)){
        cout << "Please enter x-pieces." << endl;
        return ILLEGAL;
    }
    if (turn % 2 != 0 &&(piece == X_S || piece == X_M || piece == X_L)){
        cout << "Please enter o-pieces." << endl;
        return ILLEGAL;
    }

    int row = (square - 1) / BOARDSIZE;
    int col = (square - 1) % BOARDSIZE;

    if (!isLegalMove(row, col, piece)) {
        cout << "***Invalid Move***" << endl;
        return ILLEGAL;
    }

    board[row][col] = piece;
    pieces[piece]--;

    printBoard();
    
    int winStatus = checkWin(row, col, piece);
        switch (winStatus) {
            case X_WIN:
                cout << "Player X wins!" << endl;
                return X_WIN;
            case Y_WIN:
                cout << "Player O wins!" << endl;
                return Y_WIN;
            case DRAW:
                cout << "The game ends in a draw!" << endl;
                return DRAW;
            case UNFINISHED:
                // Do nothing for UNFINISHED case
                break;
            default:
                cout << "Unknown result!" << endl;
                break;
        }
    
    turn++;
    return UNFINISHED;
}

int checkWin(int row, int col, int piece) {
    bool rowWinX = true;
    bool rowWinO = true;
    for (int i = 0; i < BOARDSIZE; ++i) {
        if (board[row][i] != X_S && board[row][i] != X_M && board[row][i] != X_L) {
            rowWinX = false;
        }
        if (board[row][i] != O_S && board[row][i] != O_M && board[row][i] != O_L) {
            rowWinO = false;
        }
    }
    if (rowWinX || rowWinO) {
        return (rowWinX) ? X_WIN : Y_WIN;
    }

    bool colWinX = true;
    bool colWinO = true;
    for (int i = 0; i < BOARDSIZE; ++i) {
        if (board[i][col] != X_S && board[i][col] != X_M && board[i][col] != X_L) {
            colWinX = false;
        }
        if (board[i][col] != O_S && board[i][col] != O_M && board[i][col] != O_L) {
            colWinO = false;
        }
    }
    if (colWinX || colWinO) {
        return (colWinX) ? X_WIN : Y_WIN;
    }
    
    bool diagWinX = true;
    bool diagWinO = true;
    for (int i = 0; i < BOARDSIZE; ++i) {
        if (board[i][i] != X_S && board[i][i] != X_M && board[i][i] != X_L) {
            diagWinX = false;
        }
        if (board[i][i] != O_S && board[i][i] != O_M && board[i][i] != O_L) {
            diagWinO = false;
        }
    }
    if (diagWinX || diagWinO) {
        return (diagWinX) ? X_WIN : Y_WIN;
    }
    
    diagWinX = true;
    diagWinO = true;
    for (int i = 0; i < BOARDSIZE; ++i) {
        if (board[i][BOARDSIZE - i - 1] != X_S && board[i][BOARDSIZE - i - 1] != X_M && board[i][BOARDSIZE - i - 1] != X_L) {
            diagWinX = false;
        }
        if (board[i][BOARDSIZE - i - 1] != O_S && board[i][BOARDSIZE - i - 1] != O_M && board[i][BOARDSIZE - i - 1] != O_L) {
            diagWinO = false;
        }
    }
    if (diagWinX || diagWinO) {
        return (diagWinX) ? X_WIN : Y_WIN;
    }

    bool draw = true;
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            if (board[i][j] == EMPTY) {
                draw = false;
                break;
            }
        }
        if (!draw) {
            break;
        }
    }
    if (draw) {
        return DRAW;
    }
    
    return UNFINISHED;
}

void passTurn(){
    turn++;
}

bool hasLegalMove(char player){
    // If a player has no pieces left return false
    if(player == 'x' && pieces[X_S] == 0 && pieces[X_M] == 0 && pieces[X_L] == 0)
        return false;

    if(player == 'o' && pieces[O_S] == 0 && pieces[O_M] == 0 && pieces[O_L] == 0)
        return false;

    // if the board has empty spaces the player can make a move
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
            if(board[i][j] == EMPTY)
                return true;

    // At this point we know the player has at least one piece and the board is full
    // so the only possibility for not being able to move is only having small pieces
    // note due to the number of pieces if we have at least one medium or large piece there
    // will be a spot on the board to move to

    if(player == 'x' && pieces[X_M] == 0 && pieces[X_L] == 0)
        return false;

    if(player == 'o' && pieces[O_M] == 0 && pieces[O_L] == 0)
        return false;

    return true;
}

int algorithmTurn(){
    int gameStatus = UNFINISHED;
    
    // Check if x is close to winning
    for (int row = 0; row < BOARDSIZE; ++row) {
        for (int col = 0; col < BOARDSIZE; ++col) {
            if (board[row][col] == EMPTY) {
                // Check win for empty
                board[row][col] = X_S;
                int winStatus = checkWin(row, col, X_S);
                if (winStatus == X_WIN) {
                    if (pieces[X_S] >= 1){
                        board[row][col] = EMPTY;
                        return takeTurn(row * BOARDSIZE + col + 1, X_S);
                    }
                    else if (pieces[X_M] >= 1){
                        board[row][col] = EMPTY;
                        return takeTurn(row * BOARDSIZE + col + 1, X_M);
                    }
                    else if (pieces[X_L] >= 1){
                        board[row][col] = EMPTY;
                        return takeTurn(row * BOARDSIZE + col + 1, X_L);
                    }
                }else
                    board[row][col] = EMPTY;
            } else if (board[row][col] == O_S) {
                // Check win for being occupied by O_S
                board[row][col] = X_S;
                int winStatus = checkWin(row, col, X_S);
                if (winStatus == X_WIN) {
                    if (pieces[X_M] >= 1){
                        board[row][col] == O_S;
                        return takeTurn(row * BOARDSIZE + col + 1, X_M);
                    }
                    else if (pieces[X_L] >= 1){
                        board[row][col] == O_S;
                        return takeTurn(row * BOARDSIZE + col + 1, X_L);
                    }
                }else
                    board[row][col] = O_S;
            } else if (board[row][col] == O_M) {
                // Check win for being occupied by O_M
                board[row][col] = X_S;
                int winStatus = checkWin(row, col, X_S);
                if (winStatus == X_WIN) {
                    if (pieces[X_L] >= 1){
                        board[row][col] == O_M;
                        return takeTurn(row * BOARDSIZE + col + 1, X_L);
                    }
                }else
                    board[row][col] = O_M;
            }
        }
    }
    
    // Check if o is close to winning
    for (int row = 0; row < BOARDSIZE; ++row) {
        for (int col = 0; col < BOARDSIZE; ++col) {
            if (board[row][col] == EMPTY) {
                // Check win for empty
                board[row][col] = O_S;
                int winStatus = checkWin(row, col, O_S);
                if (winStatus == Y_WIN) {
                    if (pieces[O_L] >= 1){
                        if (pieces[X_L] >= 1){
                            board[row][col] == EMPTY;
                            return takeTurn(row * BOARDSIZE + col + 1, X_L);
                        }
                    }
                    else if (pieces[O_M] >= 1){
                        if (pieces[X_M] >= 1){
                            board[row][col] == EMPTY;
                            return takeTurn(row * BOARDSIZE + col + 1, X_M);
                        }
                        else if (pieces[X_L] >= 1){
                            board[row][col] == EMPTY;
                            return takeTurn(row * BOARDSIZE + col + 1, X_L);
                        }
                    }
                    else if (pieces[O_S] >= 1){
                        if (pieces[X_S] >= 1){
                            board[row][col] == EMPTY;
                            return takeTurn(row * BOARDSIZE + col + 1, X_S);
                        }
                        else if (pieces[X_M] >= 1){
                            board[row][col] == EMPTY;
                            return takeTurn(row * BOARDSIZE + col + 1, X_M);
                        }
                        else if (pieces[X_L] >= 1){
                            board[row][col] == EMPTY;
                            return takeTurn(row * BOARDSIZE + col + 1, X_L);
                        }
                    }
                }else
                    board[row][col] = EMPTY;
            }
        }
    }

    // EMPTY MOVE
    if (board[1][1] == EMPTY)
        return takeTurn(5, X_L);
    
    // Random Move for Diagonal
    if (board[0][0] == EMPTY || board[0][2] == EMPTY || board[2][0] == EMPTY || board[2][2] == EMPTY){
        int emptyDia[4];
        int emptyNum = 0;
        if (board[0][0] == EMPTY) {
            emptyDia[emptyNum] = 1;
            emptyNum++;
        }
        if (board[0][2] == EMPTY) {
            emptyDia[emptyNum] = 3;
            emptyNum++;
        }
        if (board[2][0] == EMPTY) {
            emptyDia[emptyNum] = 7;
            emptyNum++;
        }
        if (board[2][2] == EMPTY) {
            emptyDia[emptyNum] = 9;
            emptyNum++;
        }
        
        int randomXPiece;
        int randomDiaPlace = rand() % emptyNum;
        
        do{
            randomXPiece = abs(2*(rand() % 3));
        }while(pieces[randomXPiece] == 0);
        
        return takeTurn(emptyDia[randomDiaPlace], randomXPiece);
    }
    
    // Random Move for Crossing
    else if (board[1][0] == EMPTY || board[0][1] == EMPTY || board[2][1] == EMPTY || board[1][2] == EMPTY){
        
        int emptyCro[4];
        int emptyNum = 0;
        if (board[1][0] == EMPTY) {
            emptyCro[emptyNum] = 2;
            emptyNum++;
        }
        if (board[0][1] == EMPTY) {
            emptyCro[emptyNum] = 4;
            emptyNum++;
        }
        if (board[2][1] == EMPTY) {
            emptyCro[emptyNum] = 6;
            emptyNum++;
        }
        if (board[1][2] == EMPTY) {
            emptyCro[emptyNum] = 8;
            emptyNum++;
        }
        
        int randomXPiece; // 0 for X_S, 1 for X_M, 2 for X_L
        int randomCroPlace = rand() % emptyNum;
        
        do{
            randomXPiece = abs(2*(rand() % 3));
        }while(pieces[randomXPiece] == 0);
        
        return takeTurn(emptyCro[randomCroPlace], randomXPiece);
    }
    
    return gameStatus; // If no suitable move is found, return UNFINISHED
}
