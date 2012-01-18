#pragma once
#include <vector>
//state.h
//Created by Eric Finn and Hillary Fotino on 2012-01-18
//State class to record state of system

class state {
	public:
		state(vector<int> &_south, vector<int> &_north, bool _boatSouth);
		int heuristic(void);
	private:
		vector<int> south;
		vector<int> north;
		bool boatSouth;
}

/* Function name: state
 * Function purpose: constructor for state class
 * Parameters:
 *		in _south: vector containing weights of people on south shore
 *		in _north: vector containing weights of people on north shore
 *		in _boatSouth: true if boat is on south shore, false otherwise
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
	return 0;
}