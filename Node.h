//
// Created by Mauricio Del Castillo on 2/17/23.
//

#ifndef GATORAVL_NODE_H
#define GATORAVL_NODE_H

#include <iostream>
using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    string name;
    int ID;
    int balFactor;

    Node(string name, int ID);
};


#endif //GATORAVL_NODE_H
