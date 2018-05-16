/**
 *Declaration of the Hunter class
 *
 *@author Adam Nichols & David Deng
 *@date April 2018
 */

#include "Board.h"

#ifndef HUNTER_H
#define HUNTER_H

using namespace std;

/**
 *@class Hunter
 *@brief The Hunter class declaration
 */
class Hunter: public Human {//Derive class Hunter from class Human
	public:
		Hunter(int initRow, int initCol, bool initInfected, Board* thisBoard);
		virtual void draw();

};

#endif //HUNTER_H
