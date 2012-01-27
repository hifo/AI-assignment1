//state.h
//Created by Eric Finn and Hillary Fotino on 2012-01-18
#pragma once

#include <vector>
#include <algorithm>
using namespace std;

//State class to record state of system

class state {
	public:
		state(vector<int> &_south, vector<int> &_north, bool _boatSouth);
		state();
		int heuristic(void);
		bool isGoalState(void);
		bool compare(state &compareTo);
		const vector<int> &getSouthSide(void);
		const vector<int> &getNorthSide(void);
		bool isBoatSouth(void);
		int getPossibleNextStates(vector<state*> &nextStates, vector<int> &costs);
		void print();
	private:
		vector<int> south;
		vector<int> north;
		bool boatSouth;
};

//helper function prototypes
int getMinVal(vector<int> &listOfVals);
void printVector(vector<int> toPrint);

/* Function name: state
 * Function purpose: constructor for state class
 * Parameters:
 *		input _south: vector containing weights of people on south shore
 *		input _north: vector containing weights of people on north shore
 *		input _boatSouth: true if boat is on south shore, false otherwise
 */
state::state(vector<int> &_south, vector<int> &_north, bool _boatSouth) {
	south = _south;
	north = _north;
	boatSouth = _boatSouth;
}

/* Function name: state
 * Function purpose: constructor for state class
 * Parameters:
 */
state::state() {
}

/* Function name: heuristic
 * Function purpose: calculates estimated cost of reaching goal from this state
 * Returns: int: estimated cost of reaching goal
 */
int state::heuristic(void) {
	//heuristic is minimum weight of individuals on the side with the boat
	if(boatSouth) {
		return getMinVal(south);
	}
	else {
		return getMinVal(north);
	}
}

/* Function name: isGoalState
 * Function purpose: determines if this state is the goal state
 * Returns: bool: true if goal state, false otherwise
 */
bool state::isGoalState(void) {
	if(south.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}

/* Function name: compare
 * Function purpose: Compare this state to another one
 * Returns: bool: true if states are the same, false otherwise
 */
bool state::compare(state &compareTo) {
	return  equal(south.begin(), south.end(), compareTo.getSouthSide().begin()) &&
	        equal(north.begin(), north.end(), compareTo.getNorthSide().begin()) &&
	        boatSouth == compareTo.isBoatSouth();
}

/* Function name: getSouthSide
 * Function purpose: determines if this state is the goal state
 * Returns: bool: true if goal state, false otherwise
 */
const vector<int> &state::getSouthSide(void) {
	return south;
}

/* Function name: getNorthSide
 * Function purpose: get vector of weights 
 * Returns: bool: true if goal state, false otherwise
 */
const vector<int> &state::getNorthSide(void) {
	return north;
}

/* Function name: isBoatSouth
 * Function purpose: determines if the boat is on the south shore in this state
 * Returns: bool: true if boat is on south shore, false otherwise
 */
bool state::isBoatSouth(void) {
	return boatSouth;
}

/* Function name: getPossibleNextStates
 * Function purpose: generates all states that can be transitioned to
 * Returns: vector of state*: vector of pointers to states that can be transitioned to from this state
 * Notes: The vector, the transition structs, and the states are allocated by this function (using new) and should be deleted by the calling function
 */
int state::getPossibleNextStates(vector<state*> &nextStates, vector<int> &costs) {
	vector<int>::iterator firstPerson;
	vector<int>::iterator secondPerson;
	int transCost;
	int stateCount = 0;
	
	if(this->isGoalState()) {
		return 0;
	}
	
	//boat is on south shore, use firstPerson and secondPerson
	if(boatSouth) {
		//handle special case of one person on south shore
		if(south.size() == 1) {
			vector<int> newSouth;
			vector<int> newNorth = north;
			newNorth.push_back(*(south.begin()));
			state *nState = new state(newSouth, newNorth, !boatSouth);
			transCost = *(south.begin());
			nextStates.push_back(nState);
			costs.push_back(transCost);
			stateCount = 1;
		}
		else {
			//create a new state for each unique combination of two people on south shore
			for(firstPerson = south.begin(); firstPerson < south.end(); firstPerson++) {
				for(secondPerson = firstPerson+1; secondPerson < south.end(); secondPerson++) {
					vector<int> newSouth;
					vector<int> newNorth = north;
					for(vector<int>::iterator tSouth = south.begin(); tSouth < south.end(); tSouth++) {
						if(tSouth != firstPerson && tSouth != secondPerson) {
							newSouth.push_back(*tSouth);
						}
						else {
							newNorth.push_back(*tSouth);
						}
					}
					state *nState = new state(newSouth, newNorth, !boatSouth);
					if(*secondPerson > *firstPerson) {
						transCost = *secondPerson;
					}
					else {
						transCost = *firstPerson;
					}
					nextStates.push_back(nState);
					costs.push_back(transCost);
					stateCount++;
				}
			}
		}
	}
	//boat is on north shore, use firstPerson
	else {
		//create a new state for each person on north shore
		for(firstPerson = north.begin(); firstPerson < north.end(); firstPerson++) {
			vector<int> newSouth = south;
			vector<int> newNorth;
			//add all but firstPerson to newNorth, add firstPerson to newSouth
			for(vector<int>::iterator tNorth = north.begin(); tNorth < north.end(); tNorth++) {
				if(tNorth != firstPerson) {
					newNorth.push_back(*tNorth);
				}
				else {
					newSouth.push_back(*tNorth);
				}
			}
			
			state *nState = new state(newSouth, newNorth, !boatSouth);
			transCost = *firstPerson;
			nextStates.push_back(nState);
			costs.push_back(transCost);
			stateCount++;
		}
	}
	return stateCount;
}

/* Function name: print
 * Function purpose: Print this state to stdout
 * Returns: void
 */
void state::print() {
	cout<<"State:\n\tBoat: ";
	if(boatSouth)
		cout<<"South";
	else
		cout<<"North";
	cout<<" shore\n"
		<<"\tSouth: ";
	printVector(south);
	cout<<"\n\tNorth: ";
	printVector(north);
	cout<<endl<<endl;
}

//Get minimum value in a vector
int getMinVal(vector<int> &listOfVals) {
	vector<int>::iterator currEl;
	int min = -1;
	for(currEl=listOfVals.begin() ; currEl < listOfVals.end(); currEl++) {
		if(*currEl < min) {
			min = *currEl;
		}
	}
	return min;
}

//print a vector of ints
void printVector(vector<int> toPrint) {
	if(toPrint.size() == 0) {
		return;
	}
	for(unsigned int idx = 0; idx < toPrint.size()-1; idx++) {
		cout<<toPrint[idx]<<", ";
	}
	cout<<toPrint[toPrint.size()-1];
}