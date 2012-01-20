//
//  assignment1.cpp
//  
//  Created by Hillary Fotino and Eric Finn on 1/18/12.
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include "state.h"
#include "node.h"
using namespace std;

void breadthFirstSearch(node *root);
void depthFirstSearch(node *root);
void aStarSearch(node *root);
bool parse_input(string file, state &initState);
void printPath(stack<node*> path);

int main(){
    string file = "input1.txt";   //change this variable to change input file
	state initState;
	bool status;
	
    status = parse_input(file, initState);
	if(status == false) {
		return 1;
	}
    
    node root(initState);
}

/* Function name: compNodesBFS
 * Function purpose: Compare two nodes for placement in a priority queue for breadth first search
 * Parameters:
 *		node &left, node &right: the nodes to compare
 * Return: bool: true if left should be later in the priority queue than right
 */
class compNodesBFS {
	public:
		bool operator()(node *left, node *right) {
			return (left->getDepth() > right->getDepth());
		}
};

/* Function name: compNodesDFS
 * Function purpose: Compare two nodes for placement in a priority queue for depth first search
 * Parameters:
 *		node &left, node &right: the nodes to compare
 * Return: bool: true if left should be later in the priority queue than right
 */
class compNodesDFS {
	public:
		bool operator()(node *left, node *right) {
			return (left->getDepth() < right->getDepth());
		}
};

/* Function name: compNodesAStar
 * Function purpose: Compare two nodes for placement in a priority queue for A* search
 * Parameters:
 *		node &left, node &right: the nodes to compare
 * Return: bool: true if left should be later in the priority queue than right
 */
class compNodesAStar {
	public:
		bool operator()(node *left, node *right) {
			return (left->getHeuristic() > right->getHeuristic());
		}
};

/* Function name: breadthFirstSearch
 * Function purpose: function to traverse the tree using the breadth first search algorithm
 * Return:
 *  void
 */
void breadthFirstSearch(node *root){
	priority_queue<node*, vector<node*>, compNodesBFS> q;
    cout << "Breadth First Search" << endl;
	//expand current node
	//add current node's children to queue
}


/* Function name: depthFirstSearch
 * Function purpose: function to traverse the tree using the depth first search algorithm
 * Return:
 *  void
 */
void depthFirstSearch(node *root){
	priority_queue<node*, vector<node*>, compNodesDFS> q;
    cout << "Depth First Search" << endl;
}


/* Function name: aStarSearch
 * Function purpose: function to traverse the tree using the A* search algorithm
 * Return:
 *  void
 */
void aStarSearch(node *root){
	priority_queue<node*, vector<node*>, compNodesAStar> q;
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

void printPath(stack<node*> path) {
	node *currNode = NULL;
	while(path.size() > 0) {
		currNode = path.top();
		path.pop();
		currNode->print();
	}
}