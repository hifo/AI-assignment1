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
    node* children;
    int cost;
    //state
    //action
}

node(){
    
}

node(node &parent){
    
}

int main(){
    node root = new node();
}