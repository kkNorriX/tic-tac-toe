//
//  gameModes.cpp
//  ticTicToe
//
//  Created by 肖旋 on 2024/5/4.
//

#include <iostream>
#include "ticTacToe.hpp"
#include "testCases.hpp"
#include "gameModes.hpp"

using namespace std;

/*--------------------------------------------------------------------------------------------------
   Local functions:
--------------------------------------------------------------------------------------------------*/
    int playerTurn(char player);
   /* Behavior:    prompts the player to make a turn
        Parameters:  'x' or 'o' (lowercase) for the current player
         Assumes:     that there is at least one possible move.
         Returns:     the game state*/

    int randomTurn(char player);
      /* Behavior:    makes a random move on the tic-tac-toe board.
        Parameters:  'x' or 'o' (lowercase) for the current player
         Assumes:     that there is at least one possible move.
         Returns:     the game state*/

    char getRandomPlayer();
      // returns 'x' or 'o' at random

/*--------------------------------------------------------------------------------------------------
   .h file function implementations:
--------------------------------------------------------------------------------------------------*/

void playerVsplayer() {
    // Reset the game
    newGame();
    printBoard();

    int currentPlayer = X_S; // X starts first
    int gameStatus = UNFINISHED;

    while (gameStatus == UNFINISHED) {
        // Determine which player's turn it is
        char playerMarker = (currentPlayer == X_S || currentPlayer == X_M || currentPlayer == X_L) ? 'X' : 'O';

        cout << playerMarker << " turn, which space would you like to play on? ";
        int square;
        cin >> square;

        cout << "Which of your remaining markers would you like to play? ";
        char pieceChar;
        cin >> pieceChar;
        int piece = markerToPiece(pieceChar);

        // Call takeTurn function
        gameStatus = takeTurn(square, piece);

        // If the move was illegal, repeat the same player's turn
        if (gameStatus == ILLEGAL) {
            continue;
        }

        // Switch player for the next turn
        currentPlayer = (currentPlayer == X_S || currentPlayer == X_M || currentPlayer == X_L) ? O_S : X_S;
    }
}

/*------------------------------------------------------------------------------------------------*/

void playerVsRandom(){
    newGame();
    printBoard();
    
    int currentPlayer = X_S; // X starts first
    int gameStatus = UNFINISHED;
    char RandomPlayer = getRandomPlayer();
    
    cout << "random piece: " << RandomPlayer << endl;
    
    while (gameStatus == UNFINISHED) {
        // Determine which player's turn it is
        
        if (RandomPlayer == 'x') {
            gameStatus = randomTurn('x');
            if (gameStatus != UNFINISHED) // check if the game is finished
                break;
            gameStatus = playerTurn('o');
        }
        // Random turn
        else {
            gameStatus = playerTurn('x');
            if (gameStatus != UNFINISHED) // check if the game is finished
                break;
            gameStatus = randomTurn('o');
        }
        
        if (gameStatus == ILLEGAL) {
            continue;
        }
        currentPlayer = (currentPlayer == X_S || currentPlayer == X_M || currentPlayer == X_L) ? O_S : X_S;

    }
}

/*------------------------------------------------------------------------------------------------*/

void playerVsAlgorithm(){
    newGame();
    printBoard();
    
    int currentPlayer = X_S; // X starts first
    int gameStatus = UNFINISHED;
    
    cout << "AI will run x's turn." << endl;
    
    while (gameStatus == UNFINISHED) {
        // Determine which player's turn it is
        char playerMarker = (currentPlayer == X_S || currentPlayer == X_M || currentPlayer == X_L) ? 'X' : 'O';
        
        if (playerMarker == 'X') {
            gameStatus = algorithmTurn();
        } else {
            gameStatus = playerTurn('o');
        }
        
        if (gameStatus == ILLEGAL) {
            continue;
        }
        
        currentPlayer = (currentPlayer == X_S || currentPlayer == X_M || currentPlayer == X_L) ? O_S : X_S;
    }
}

/*------------------------------------------------------------------------------------------------*/

void randomVsAlgorithm(){
    newGame();
    printBoard();
    
    int currentPlayer = X_S; // X starts first
    int gameStatus = UNFINISHED;
        
    cout << "AI will run x's turn." << endl;
    
    while (gameStatus == UNFINISHED) {
        // Determine which player's turn it is
        char playerMarker = (currentPlayer == X_S || currentPlayer == X_M || currentPlayer == X_L) ? 'X' : 'O';
        
        if (playerMarker == 'X') {
            gameStatus = algorithmTurn();
        } else {
            gameStatus = randomTurn('o');
        }
        
        if (gameStatus == ILLEGAL) {
            continue;
        }
        
        currentPlayer = (currentPlayer == X_S || currentPlayer == X_M || currentPlayer == X_L) ? O_S : X_S;
    }
}

/*--------------------------------------------------------------------------------------------------
   Local function implementations
--------------------------------------------------------------------------------------------------*/

int playerTurn(char player){
    int gameStatus = UNFINISHED;


    cout << player << " turn, which space would you like to play on? ";
    int square;
    cin >> square;

    cout << "Which of your remaining markers would you like to play? ";
    char pieceChar;
    cin >> pieceChar;
    int piece = markerToPiece(pieceChar);
    
    // Call takeTurn function
    gameStatus = takeTurn(square, piece);
    
    return gameStatus;
}

/*------------------------------------------------------------------------------------------------*/

int randomTurn(char player){
    int gameState, piece, square;

    // implements the most basic form of random move selection (guess and check until it works)
    do{
            // 1. select a random piece ('x' is 0, 2, 4 and 'o' is 1, 3, 5)
            if(player == 'x')
            //TODO: tidy this up and remove the magic numbers
                piece = 2*(rand() % 3);
            else
                piece = 2*(rand() % 3) + 1;

            // 2. select a random square
            square = rand() % 9 + 1;
            // 3. try to make that move
            gameState = takeTurn(square, piece);
    }while(gameState == ILLEGAL);

    return gameState;

}

/*------------------------------------------------------------------------------------------------*/

char getRandomPlayer(){
   srand (time(NULL)); // initialize the random number generator

   if(rand() % 2 == 0){
        return 'o';
    }else{
        return 'x';
    }
}
