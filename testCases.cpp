//
//  testCases.cpp
//  ticTicToe
//
//  Created by 肖旋 on 2024/4/7.
//

#include <iostream>
#include "ticTacToe.hpp"
#include "testCases.hpp"
#include "gameModes.hpp"


using namespace std;


void test_takeTurn01(){
    int gameState; // will be used for storing the gameState returned from takeTurn

    newGame();

    cout << "Testing a full game with no illegal moves:\n";
    printBoard();
    cout << endl;
    takeTurn(1, X_L);

    printBoard();
    cout << endl;
    takeTurn(2, O_M);

    printBoard();
    cout << endl;
    takeTurn(3, X_S);

    printBoard();
    cout << endl;
    takeTurn(5, O_L);

    printBoard();
    cout << endl;
    gameState = takeTurn(2, X_L);
    printBoard();

    if(gameState == X_WIN)
        cout << "Test Passed\n";
    else
        cout << "Test Failed\n";
}


void test_takeTurn02(){
    cout << "Testing O going first illegally:\n";

    newGame();

    if(takeTurn(1, O_L) == ILLEGAL)
        cout << "Test Passed\n";
    else
        cout << "Test Failed\n";
}
