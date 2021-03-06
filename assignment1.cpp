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

typedef enum {BFS, DFS, ASTAR} t_algorithm;

template <t_algorithm algo> void genericSearch(node *root);
void breadthFirstSearch(node *root);
void depthFirstSearch(node *root);
void aStarSearch(node *root);
bool parse_input(string file, state &initState);
void printPath(stack<node*> &path);

int main(int argc, char* argv[]){
	string file;
	state initState;
	bool status;
	if(argc > 1) {
		file = argv[1];
	}
	else {
		cout << "Enter the name of the input file" << endl;
		cin >> file;
	}
    status = parse_input(file, initState);
	if(status == false) {
		return 1;
	}
    
    node rootBFS(initState);
	node rootDFS(initState);
	node rootASt(initState);
	genericSearch<BFS>(&rootBFS);
	genericSearch<DFS>(&rootDFS);
	genericSearch<ASTAR>(&rootASt);
	return 0;
}


/* Function name: compNodes
 * Function purpose: Compare two nodes for placement in a priority queue for given algorithm
 * Parameters:
 *		node &left, node &right: the nodes to compare
 * Return: bool: true if left should be later in the priority queue than right
 */
template<t_algorithm algo>
class compNodes {
	public:
		bool operator()(node *left, node *right) {
			if(left == NULL || right == NULL) {
				return false;
			}
			switch(algo) {
				case BFS:
					return (left->getDepth() > right->getDepth());
				case DFS:
					return (left->getDepth() < right->getDepth());
				case ASTAR:
					return ((left->getHeuristic() + left->getCost()) >
							(right->getHeuristic() + right->getCost()));
				default:
					return false;
			}
		}
};

/* Function name: genericSearch
 * Function purpose: function to traverse the given tree using the given search algorithm
 * Parameters:
 *		t_algorithm algo: Search algorithm to use to traverse the tree
 *		node *root: Root node of the tree to traverse
 * Return:
 *  void
 */
template <t_algorithm algo>
void genericSearch(node *root) {
	priority_queue<node*, vector<node*>, compNodes<algo> > q;
	node *currNode = NULL;
	vector<node*> currNodeChildren;
	node *goalNode = NULL;
	stack<node*> path;
	int totalCost = 0;
	int expandCount = 0;
	bool goalFound = false;
	
	if(root == NULL) {
		return;
	}
	
    switch(algo) {
		case BFS:
			cout<<"Breadth First Search";
			break;
		case DFS:
			cout<<"Depth First Search";
			break;
		case ASTAR:
			cout<<"A* Search";
			break;
		default:
			cout<<"Unknown Search Algorithm";
			break;
	}
	
	q.push(root);

	while((q.size() > 0) && !goalFound) {
		//get first node
		currNode = q.top();
		q.pop();
		//expand node
		currNode->expand();
		expandCount++;
		//add node's children to queue
		currNodeChildren = currNode->getChildren();
		for(vector<node*>::iterator it = currNodeChildren.begin(); it < currNodeChildren.end(); it++) {
			q.push(*it);
			//check for end condition in node's children
			if((*it)->isGoalNode()) {
				goalNode = *it;
				goalFound = true;
				break;
			}
		}
	}
	totalCost = goalNode->tracePathToHere(path);
	cout<<" "<<totalCost<<" "<<expandCount<<endl;
	printPath(path);
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
	
	if(!input.is_open()) {
		cerr<<"Unable to open file: "<<file<<endl;
		return false;
	}
	
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

void printPath(stack<node*> &path) {
	node *currNode = NULL;
	while(path.size() > 0) {
		currNode = path.top();
		path.pop();
		currNode->print();
	}
}
