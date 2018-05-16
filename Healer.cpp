/**
 * @file Healer.cpp
 * @brief The Healer class implementation file.
 *
 * -- Enter the correct information below, then remove this line.
 * @author Adam Nichols
 * @author David Deng
 * @date April 19th, 2018
 */

#include <cstdlib>
#include <iostream>

#include "Healer.h"
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
Healer::Healer(int initRow, int initCol, bool initInfected, Board* theBoard)
	: Human(initRow, initCol, initInfected, theBoard) {
    myType = healer;
}

void Healer::draw(){
	cout << conio::gotoRowCol(row+1,col+1);
	cout << conio::bgColor(conio::BLUE);
	cout << 'H' << conio::resetAll() << flush;

}
