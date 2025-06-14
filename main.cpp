//
//  main.cpp
//  ticTicToe
//
//  Created by 肖旋 on 2024/4/4.
//

#include <iostream>
#include "ticTacToe.hpp"
#include "testCases.hpp"
#include "gameModes.hpp"

using namespace std;

int main() {
    int menuOption;
        do{
            cout << "Please Select one of the Following Options\n";
            cout << "  0. Show board map\n";
            cout << "  1. Player vs Player\n";
            cout << "  2. Player vs Random\n";
            cout << "  3. Player vs Algorithm\n";
            cout << "  4. Algorithm vs Random (1 time)\n";
            cout << "  5. Algorithm vs Randam (100 times)\n";
            cout << "  6. Algorithm vs Algorithm (100 times)\n";
            cout << "  7. Exit\n";
            cout << "  101. Tests a full basic game\n";
            cout << "  102. Tests O going out of turn\n";

            cin >> menuOption;

            switch(menuOption){
                case 0:
                    printBoardMap();
                    break;
                case 1:
                    playerVsplayer();
                    break;
                case 2:
                    playerVsRandom();
                    //1. Make a matrix of legal moves
                    //2. count the legal moves(15)
                    //3. pick a random number between 1 & 15
                    //4. make that move
                    //*need bool isLegalMove(maybe 4 lines of code, all 10/12 lines of code)
                    break;
                case 3:
                    // player vs algorithm
                    playerVsAlgorithm();
                    break;
                case 4:
                    // algorithm vs random (1 time)
                    randomVsAlgorithm();
                    break;
                case 5:
                    // algorithm vs random (100 times)
                    break;
                case 6:
                    // algorithm vs algorithm (100 times)
                    break;
                case 7:
                    // exit
                    break;
                case 101:
                   // Tests a full basic game
                   test_takeTurn01();
                   break;
                case 102:
                   // Tests O going out of turn
                   test_takeTurn02();
                   break;
                default:
                    newGame();
                    printBoard();
                    cout << "Not a valid option." << endl;
            }
        }while(menuOption != 7);
    return 0;
}
