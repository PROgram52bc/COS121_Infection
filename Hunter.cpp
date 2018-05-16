/**
 * @file Hunter.cpp
 * @brief The Hunter class implementation file.
 *
 * -- Enter the correct information below, then remove this line.
 * @author Adam Nichols
 * @author David Deng
 * @date April 19th, 2018
 */

#include <cstdlib>
#include <iostream>

#include "Hunter.h"
#include "Human.h"
#include "conio.h"

using namespace std;

/**
 * @brief The Human class constructor.
 * This function initializes the row, col, infected, and board variables.
 *
 * @param initRow the initial human row location.
 * @param initCol the initial human column location.
 * @param initInfected whether the human is initially infected.
 * @param theBoard a pointer to the board (used to ask board whether a proposed move is ok).
 */
Hunter::Hunter(int initRow, int initCol, bool initInfected, Board* theBoard)
	: Human(initRow, initCol, initInfected, theBoard) {
    myType = hunter;
}

void Hunter::draw(){
	cout << conio::gotoRowCol(row+1,col+1);
	cout << conio::bgColor(conio::YELLOW);
	cout << '#' << conio::resetAll() << flush;

}
