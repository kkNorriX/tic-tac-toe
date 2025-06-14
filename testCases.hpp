//
//  testCases.hpp
//  ticTicToe
//
//  Created by 肖旋 on 2024/4/7.
//
// This file stores several test cases for the ticTacToe.cpp file

#ifndef testCases_hpp
#define testCases_hpp

#include <stdio.h>

void test_takeTurn01();
/* Simulates a basic game of tic-tac-toe where x wins
   Testing:
        Placements:       Yes
        Captures:         Yes
        Invalid Moves:     No
        Winner:             X
*/

void test_takeTurn02();
/* Simulates O trying to play first turn
   Testing:
        Placements:       N/A
        Captures:         N/A
        Invalid Moves:    Yes
        Winner:           N/A
*/

#endif /* testCases_hpp */
