//
//  assignment1.cpp
//  
//  Created by Hillary Fotino and Eric Finn on 1/18/12.
//

#include <iostream>
#include <fstream>
#include <string>
#include "state.h"
#include "node.h"
using namespace std;

void breadthFirstSearch();
void depthFirstSearch();
void aStarSearch();
bool parse_input(string file, state &initState);

int main(){
    string file = "input1.txt";   //change this variable to change input file
	state initState;
    parse_input(file, initState);
    
    node root(initState);
}


/* Function name: breadthFirstSearch
 * Function purpose: function to traverse the tree using the breadth first search algorithm
 * Return:
 *  void
 */
void breadthFirstSearch(){
    cout << "Breadth First Search" << endl;
}


/* Function name: depthFirstSearch
 * Function purpose: function to traverse the tree using the depth first search algorithm
 * Return:
 *  void
 */
void depthFirstSearch(){
    cout << "Depth First Search" << endl;
}


/* Function name: aStarSearch
 * Function purpose: function to traverse the tree using the A* search algorithm
 * Return:
 *  void
 */
void aStarSearch(){
    cout << "A* search" << endl;
}

/* Function name: parse_input
 * Function purpose: Given a filename and state object, parses file to set initial state
 * Parameters:
 *  file: String: The name of the file that needs to be parsed
 *	initState: state&: Reference to state object to set to initial state from file
 * Return:
 *  bool: true on success, false on failure
 */
bool parse_input(string file, state &initState){
    ifstream input;
	int curElement;
	unsigned int numElements;
	vector<int> initSouth;
	vector<int> initNorth;
	bool result = true;
	
	input.open(file.c_str(), ifstream::in);
	
	//get element count (1st number in file)
	input>>numElements;
	
	//get list of elements
	while(input.good()) {
		input>>curElement;
		initSouth.push_back(curElement);
	}
	
	//check that we read all elements and didn't read too many
	if(initSouth.size() != numElements) {
		result = false;
		cerr<<"Parsing error: Mismatch between given element count and actual element count"<<endl;
	}
	
	initState = state(initSouth, initNorth, true);
	input.close();
	return result;
}