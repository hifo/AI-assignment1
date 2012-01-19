#pragma once
#include <vector>
//
//  node.h
//
//  Created by Hillary Fotino and Eric Finn on 1/18/12.
//

/*
 *  Class for nodes for tree creation and traversal
 */

class node{
public:
    node(state &_currState); //constructor for root node
    node(node *_parent, state &_currState, int _cost); //constructor for child nodes
    ~node();
	void expand();
	int getDepth();
private:
    void addChild(node &child);
	void addNextState(state &nextState);
    node *parent;
    vector<node*> children;
    int cost;
    int depth;
    state currState;
};

/* Function name: node
 * Function purpose: constructor for node class, used for the root which has no parent
 * Parameters: 
 *      state &_currState: the state associated with the node being constructed
 */
node::node(state &_currState){
    this->parent = NULL;
    this->cost = 0;
    this->depth = 0;
	this->currState = _currState;
}


/* Function name: node
 * Function purpose: constructor for node class for child nodes
 * Parameters: 
 *      node &_parent: the node which is the parent node for the node being constructed
 *		state &_currState: the state associated with the node being constructed
 *		int _cost: the cost to get from the parent node to the node being constructed
 */
node::node(node &_parent, state &_currState, int _cost){
    this->parent = &_parent;
	this->cost = _cost;
    this->depth = this->parent->getDepth()+1;
	this->currState = _currState;
}

/* Function name: ~node
 * Function purpose: destructor for node class
 */
node::~node() {
	for(vector<node*>::iterator currChild = children.begin(); currChild < children.end(); currChild++) {
		delete *currChild;
	}
}

/* Function name: addChild
 * Function purpose: adds a child to a given node
 * Parameters:
 *		node &child: node to add as a child to this node
 * Returns: void
 */
void node::addChild(node &child){
    this->children.push_back(&child);
}

/* Function name: expand
 * Function purpose: create and add children states to this node
 * Returns: void
 */
void node::expand() {
	vector<state*> nextStates;
	vector<int> costs;
	int nextStates = 0;
	nextStates = currState->getPossibleNextStates(nextStates, costs);
	//iterate through nextStates, adding a node and its corresponding cost for each state
	for(int index = 0; index < nextStates; index++) {
		addNextState(nextStates[index], costs[index]);
	}
}

/* Function name: addNextState
 * Function purpose: Add a possible next state as a child node to the tree
 * Parameters:
 *		state &nextState: the possible next state for which to create a node
 *		int cost: the cost to get from this state to the possible next state
 * Returns: void
 */
void node::addNextState(state &nextState, int cost) {
	node *child = new node(*this, nextState, cost);
	this->children.push_back(child);
}
