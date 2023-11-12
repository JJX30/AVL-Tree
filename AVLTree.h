//
// Created by Mauricio Del Castillo on 2/17/23.
//

#ifndef GATORAVL_AVLTREE_H
#define GATORAVL_AVLTREE_H

#include <string>
#include "Node.h"
#include <vector>
using namespace std;

class AVLTree {
    Node* treeroot;
    int numNodes;
public:
    AVLTree();
    Node* getRoot();
    void setRoot(Node* root);
    Node* insert(Node* root, const string& name, int ID);
    int balanceFactor(Node* root);
    int height(Node* root);
    static Node* rotateL(Node *node);
    static Node* rotateR(Node *node);
    static Node* rotateRL(Node *node);
    static Node* rotateLR(Node *node);
    void inOrder(Node* root, vector<Node*> &nodes);
    void preOrder(Node* root, vector<Node*> &nodes);
    void postOrder(Node* root, vector<Node*> &nodes);
    void printInorder(Node* root);
    void printPreorder(Node* root);
    void printPostorder(Node* root);
    void printLevel(Node* root);
    bool searchID(Node* root, int ID);
    bool ifIDExists(Node* root, int ID);
    bool searchName(Node* root, string name);
    static Node* leftMost(Node* node);
    Node* remove(Node* root, int ID);
    Node* removeInorder(Node* root, int count);
};


#endif //GATORAVL_AVLTREE_H
