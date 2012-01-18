//
//  node.h
//
//  Created by Hillary Fotino and Eric Finn on 1/18/12.
//

#ifndef _node_h
#define _node_h

/*
 *  Class for nodes for tree creation and traversal
 */

class node{
public:
    node(node &parent);
    node();
    ~node();
private:
    node parent;
    node[] children;
    int cost;
    //state
    //action
    void addChild(node* child);
}

/* Function name: node
 * Function purpose: constructor for node class, used for the root which has no parent
 * Parameters: 
 *      none
 */
node::node(){
    this->parent = NULL;
    this->cost = 0;
}


/* Function name: node
 * Function purpose: constructor for node class
 * Parameters: 
 *      node &parent: the node which is the parent node for the node being constructed
 */
node::node(node &parent){
    this->parent = &parent;
}


/* Function name: addChild
 * Function purpose: adds a child to a given node
 * Returns: void
 */
void addChild(node &child){
    for (int i=0; i < this->children.length; i++) {
        if(this->children[i] == NULL){
            this->children[i] = &child;
        }
    }
}


#endif
