//
//  assignment1.cpp
//  
//  Created by Hillary Fotino and Eric Finn on 1/18/12.
//

#include <iostream>
using namespace std;

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
    addChild(node* child);
}

node::node(){
    this->parent = NULL;
}

node::node(node &parent){
    this->parent = &parent;
}

node::addChild(node &child){
    for (int i=0; i < this->children.length; i++) {
        if(this->children[i] == NULL){
            this->children[i] = &child;
        }
    }
}

int main(){
    node root = new node();
}