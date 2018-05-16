/**
 *Declaration of the Healer class
 *
 *@author Adam Nichols & David Deng
 *@date April 2018
 */

#include "Board.h"

#ifndef HEALER_H
#define HEALER_H

using namespace std;

/**
 *@class Healer
 *@brief The Healer class declaration
 */
class Healer: public Human {//Derive class Healer from class Human
	public:
		Healer(int initRow, int initCol, bool initInfected, Board* thisBoard);
		virtual void draw();

};

#endif //Healer_H
