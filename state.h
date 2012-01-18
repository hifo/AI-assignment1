#pragma once
#include <vector>
//state.h
//Created by Eric Finn and Hillary Fotino on 2012-01-18
//State class to record state of system

int getMinVal(vector<int> &listOfVals);

class state {
	public:
		state(vector<int> &_south, vector<int> &_north, bool _boatSouth);
		int heuristic(void);
		bool isGoalState(void);
		int compare(state &compareTo);
		const vector<int> &getSouthSide(void);
		const vector<int> &getNorthSide(void);
		bool isBoatSouth(void);
	private:
		vector<int> south;
		vector<int> north;
		bool boatSouth;
}

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
