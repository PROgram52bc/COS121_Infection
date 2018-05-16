/**
 * @file Board.cpp
 * @brief Board class implementation (also called 'definition') file.
 * @author Stefan Brandle
 * @date March 2012
 */

#include <iostream>
#include <cstdlib>
#include <unistd.h>

// When writing a class implementation file, you must "#include" the class
// declaration file.
#include "Board.h"

// We also use the conio namespace contents, so must "#include" the conio declarations.
#include "conio.h"

#define RUNTIME 120

/**
 * @brief The Board class constructor, responsible for intializing a Board object.
 * The Board constructor is responsible for initializing all the Board object variables.
 *
 * @param rows The number of rows to make the board.
 * @param cols The number of columns to make the board.
 * @param numberOfHumans The number of humans to place on the board.
 */
Board::Board(int rows, int cols, int numberOfHumans) {
    numHumans = numberOfHumans;
    numRows = rows;
    numCols = cols;
    currentTime = 0;
    uSleepTime = 250000;
    numInfected=0;
}

/**
 * @brief The Board class destructor.
 * The Board destructor is responsible for any last-minute cleaning 
 * up that a Board object needs to do before being destroyed. In this case,
 * it needs to return all the memory borrowed for creating the Human objects.
 */
Board::~Board() {
    for(int pos=0; pos<numHumans; ++pos) {
	delete humans[pos];
    }
}

/**
 * @brief function that runs the simulation
 * Creates human objects, infects one human, then runs simulation until all are infected.
 */
void Board::run() {
    int row, col;

    // Creates 'Human' objects and sets the array pointers to point at them.
    for(int pos=0; pos<numHumans; ++pos) {

		row = pos%numRows;       // row will be in range(0, numRows-1)
		col = random()%numCols;  // col will be in range(0, numCols-1)
		// Create and initialize another Human. 
		// Parameters are  row on board, col on board, initialy infected, 
		// and a pointer to this board object ('this').
		switch (rand()%20) {
			case 0:
			case 1:
			case 2:
				humans[pos] = new Hunter(row, col, false, this); 
				break;
			case 3:
				humans[pos] = new Healer(row, col, false, this); 
				break;
			case 4:
			case 5:
			case 6:
				humans[pos] = new Human(row, col, false, this); 
				humans[pos]->setInfected();
				break;
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			default:
				humans[pos] = new Human(row, col, false, this); 
		}


    }
    // Infect a random human in the range 0 to numHumans-1

	
    //humans[random()%numHumans]->setInfected();

    for(currentTime=0;; ++currentTime) {
		if (currentTime > RUNTIME || allInfected() || (numInfected == 0 && currentTime>0))
			break;
		// Clear screen before every new time unit
		cout << conio::clrscr() << flush;

		// Tell each human to try moving
		for(int pos=0; pos<numHumans; ++pos) {
			// if human dead then don't move
			if (humans[pos]->isAlive())
				humans[pos]->move();
		}

		// Deal with infection propagation.
		processInfection();

		// Tell each human to draw itself on board with updated infection status
		for(int pos=0; pos<numHumans; ++pos) {
			humans[pos]->draw();
		}

		// Print statistics.
		cout << conio::gotoRowCol(numRows+3, 1) 
			<< "Time=" << currentTime 
			<< " Total humans=" << numHumans
			<< " Total infected=" << numInfected << flush;

		// Sleep specified microseconds
		usleep(uSleepTime);
    }
	cout << conio::gotoRowCol(numRows+4, 1) << flush << endl;
	if (allInfected())
		cout << "\
		  _____        __          _           _                       \n\
		 |_   _|      / _|        | |         | |                      \n\
		   | |  _ __ | |_ ___  ___| |_ ___  __| | __      _____  _ __  \n\
		   | | | '_ \\|  _/ _ \\/ __| __/ _ \\/ _` | \\ \\ /\\ / / _ \\| '_ \\ \n\
		  _| |_| | | | ||  __/ (__| ||  __/ (_| |  \\ V  V / (_) | | | |\n\
		 |_____|_| |_|_| \\___|\\___|\\__\\___|\\__,_|   \\_/\\_/ \\___/|_| |_|\n\
		" << endl;
	else if (numInfected == 0)
		cout << "\
		  _    _\n\
		 | |  | |\n\
		 | |__| |_   _ _ __ ___   __ _ _ __  ___  __      _____  _ __  \n\
		 |  __  | | | | '_ ` _ \\ / _` | '_ \\/ __| \\ \\ /\\ / / _ \\| '_ \\ \n\
		 | |  | | |_| | | | | | | (_| | | | \\__ \\  \\ V  V / (_) | | | |\n\
		 |_|  |_|\\__,_|_| |_| |_|\\__,_|_| |_|___/   \\_/\\_/ \\___/|_| |_|\n\
		" << endl;
	else if (currentTime > RUNTIME)
		cout << "\
          _______ _      \n\
         |__   __(_)     \n\
            | |   _  ___ \n\
            | |  | |/ _ \\\n\
            | |  | |  __/\n\
            |_|  |_|\\___|\n\
			" << endl;


    // Position the cursor so prompt shows up on its own line
	cout << endl;
}

/**
 * @brief Determines whether or not all humans are infected.
 * @return If even one human is uninfected, returns false. Otherwise, returns true.
 */
bool Board::allInfected() {
    for(int i=0; i<numHumans; ++i) {
		if(humans[i]->isInfected() == false && humans[i]->getType() == normal) return false;
    }

    return true;
}

/**
 * @brief The function that handles one infection cycle to determine what new infections
 *        are present.
 * For each pair of adjacent humans in the simulation, processInfection() makes sure that if 
 * one is infected, the other becomes infected as well.
 */
void Board::processInfection() {
	for( int i=0; i<numHumans; ++i ) {
		for( int j=i+1; j<numHumans; ++j ) {
			if( isNextTo(humans[i], humans[j]) ){
				// Checking the types of i and j
				// if hunter meets infected human
				if( humans[i]->getType() == hunter && humans[j]->isInfected()) {
					humans[j]->setDead();
				} else if( humans[j]->getType() == hunter && humans[i]->isInfected()) {
					humans[i]->setDead();
				}
				// if infected human meets normal human
				else if( humans[i]->isInfected() && humans[j]->getType()==normal && !humans[j]->isInfected()) {
					humans[j]->setInfected();
				} else if ( humans[j]->isInfected() && humans[i]->getType()==normal && !humans[i]->isInfected()) {
					humans[i]->setInfected();
				}
				// if infected human meets healer
				else if( humans[i]->isInfected() && humans[j]->getType()==healer) {
					humans[i]->heal();
				} else if ( humans[j]->isInfected() && humans[i]->getType()==healer) {
					humans[j]->heal();
				}
			}
		}
	}

	// Reset the board 'numInfected' count and recount how many are infected.
	numInfected = 0;
	for( int i=0; i<numHumans; ++i ) {
		if( humans[i]->isInfected() && humans[i]->isAlive() ) numInfected++;
	}
}

/**
 * @brief The function that determines whether a particular move can happen.
 *        If the move would go off the board, or land on the same position as another
 *        human, the function returns false (do not move). Otherwise, it returns true (ok to proceed).
 * @param[in] row the row the human wishes to move to.
 * @param[in] col the col the human wishes to move to.
 * @return Whether the human calling this function may move to the specified row and column.
 */
bool Board::tryMove(int row, int col) {
    int tryRow, tryCol=-1;

    // If off board, the move is not permitted
    if( row<0 || row>=numRows || col<0 || col>=numCols ) return false;

    // Else if another human is on the same location, the move is not permitted
    for(int i=0; i<numHumans; ++i) {
        humans[i]->getLocation(tryRow, tryCol);
	if( row==tryRow && col==tryCol ) return false;
    }

    // No problems, so the move is permitted
    return true;
}

/**
 * @brief The function that determines whether two humans are on adjacent squares.
 * @param h1 pointer to first human object.
 * @param h2 pointer to second human object.
 * @return Whether or not h1 and h2 are on adjacent squares.
 */
bool Board::isNextTo(Human *h1, Human* h2) {
    // Get human location information
    int h1Row, h1Col;
    h1->getLocation(h1Row, h1Col);
    int h2Row, h2Col;
    h2->getLocation(h2Row, h2Col);

    // Return whether h1 and h2 are on adjacent squares in any direction 
    // (horizontally, vertically, diagonally).
    return abs(h1Row-h2Row)<=1 && abs(h1Col-h2Col)<=1;
}

