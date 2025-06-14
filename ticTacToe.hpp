//
//  ticTacToe.hpp
//  ticTicToe
//
//  Created by 肖旋 on 2024/4/4.
//

#ifndef ticTacToe_hpp
#define ticTacToe_hpp

#include <stdio.h>


/*--------------------------------------------------------------------------------------------------
Define some variables and constants
--------------------------------------------------------------------------------------------------*/
// Define the different pieces, note these need to align with MARKERS[]
const int X_S = 0;
const int O_S = 1;
const int X_M = 2;
const int O_M = 3;
const int X_L = 4;
const int O_L = 5;

// Define an empty space
const int EMPTY = 6;

// Define the board state
const int ILLEGAL    = -1;
const int UNFINISHED = 0;
const int X_WIN      = 1;
const int Y_WIN      = 2;
const int DRAW       = 3;

// Define a string of characters to lookup each marker
//   ie: marker[X_L] will show '#'
//       marker[EMPTY] will show ' ';
const char MARKERS[] = "xoXO#@ ";

// Create the board
const int BOARDSIZE = 3;

// at the beginning of the game there will be 2 of each piece
const int NUMPIECES = 6;
const int NUMPERPIECE = 2;

/*--------------------------------------------------------------------------------------------------
Define some functions
--------------------------------------------------------------------------------------------------*/

void newGame();
    // resets the board to empty and the number of pieces to 2 each

void printBoard();
    // prints the board for the user to see

void printBoardMap();
    // prints the map of the board

int getLocation(int square);
    // returns the piece (X_S, O_S...) or EMPTY for a given spot

int markerToPiece(char piece);
    // returns the piece number from the charecter; ILLEGAL if it is invalid
    // for instante 'x' would return X_S

int getBoard(int board[BOARDSIZE][BOARDSIZE]);
    // return a link to the board location

int takeTurn(int square, int piece);
    /* sets the piece at location to piece
        this places the piece at the location and removes it from the users remaining pieces
       NOTE: If the move is illegal, then this function outputs "Illegal Move" and returns ILLEGAL
           ILLEGAL moves are moves that are not on the board, playing out of turn, playing a piece
           that you have run out of, an invalid capture (for instance placing an x on an @.)
        RETURNS: X_WIN if player X wins
                 Y_WIN if player Y wins
                 DRAW if there is not a winner
                 ILLEGAL *see note above */

int checkWin(int row, int col, int piece);
    //check whether player wins

void passTurn();
    /* if the player can't make a move or wants to skip their turn, they can pass. */

bool hasLegalMove(char player);
    /* returns true if player has a legal move remaining. Player can be 'x' or 'o' (small case) */

int algorithmTurn();
    //used in playerVsAlgorithm

#endif /* ticTacToe_hpp */
