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

node::node(){
    this->parent = NULL;
}

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
