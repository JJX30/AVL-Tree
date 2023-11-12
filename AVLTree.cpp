//
// Created by Mauricio Del Castillo on 2/17/23.
//
#include "AVLTree.h"
#include <vector>
#include <utility>
#include "Node.h"
#include <iomanip>

AVLTree::AVLTree() {
    this->treeroot = nullptr;
    this->numNodes = 0;
}

Node *AVLTree::insert(Node* root,const string& name, int ID) {

    // insertion determining left or right
    if(root == nullptr) {

        // if at the end add node
        Node *temp = new Node(name, ID);
        cout << "successful" << endl;
        this->numNodes++;
        return temp;
    }else if (root->ID > ID) {
        // left insertion recursive call
        root->left = insert(root->left, name, ID);
    }else if (root->ID < ID) {
        // right insertion recursive call
        root->right = insert(root->right, name, ID);
    }else {
        // else there was an unsuccessful attempt
        cout << "unsuccessful" << endl;
        return root;
    }

    root->balFactor = balanceFactor(root);

    // threshold of 1 to -1
    // based on balance factor sign and if the ID is being inserted to the right or left of its parent, the rotation is decided upon
    if (root->balFactor > 1 && ID < root->left->ID){
        return rotateR(root);
    } else if (root->balFactor < -1 && ID > root->right->ID) {
        return rotateL(root);
    } else if (root->balFactor > 1 && ID > root->left->ID) {
        return rotateLR(root);
    } else if (root->balFactor < -1 && ID < root->right->ID) {
        return rotateRL(root);
    }
    return root;
}

// balance factor
int AVLTree::balanceFactor(Node *root) {
    if (root == nullptr) {
        return 0;
    } else {
        // recursive call to total the heights of whole tree
        return height(root->left) - height(root->right);
    }
}

// height function
int AVLTree::height(Node *root) {
    if(root == nullptr)
        return 0;
    int left = height(root->left);
    int right = height(root->right);
    return 1 + max(left, right);
}

// left rotate
Node *AVLTree::rotateL(Node *node) {
    Node* grandChild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandChild;
    return newParent;
}

// right rotate
Node *AVLTree::rotateR(Node *node) {
    Node* grandChild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandChild;
    return newParent;
}

// right rotate left rotate
Node *AVLTree::rotateRL(Node *node) {
    Node* greatGrandChild = node->right->left->right;
    Node* newChild = node->right->left;
    Node* grandChild = node->right;
    node->right = newChild;
    newChild->right = grandChild;
    grandChild->left = greatGrandChild;
    Node* newParent = rotateL(node);
    return newParent;
}

// left rotate right rotate
Node *AVLTree::rotateLR(Node *node) {
    Node* greatGrandChild = node->left->right->left;
    Node* newChild = node->left->right;
    Node* grandChild = node->left;
    node->left = newChild;
    newChild->left = grandChild;
    grandChild->right = greatGrandChild;
    Node* newParent = rotateR(node);
    return newParent;
}

Node *AVLTree::getRoot() {
    return this->treeroot;
}

void AVLTree::setRoot(Node *root) {
    this->treeroot = root;
}

void AVLTree::inOrder(Node *root, vector<Node *> &nodes) {
    // push noes into vector in left root right
    if (root == nullptr)
        return;
    inOrder(root->left, nodes);
    nodes.push_back(root);
    inOrder(root->right, nodes);
}

void AVLTree::preOrder(Node *root, vector<Node *> &nodes) {
    // push nodes into vector root left right
    if (root == nullptr)
        return;
    nodes.push_back(root);
    preOrder(root->left, nodes);
    preOrder(root->right, nodes);

}

void AVLTree::postOrder(Node *root, vector<Node *> &nodes) {
    // push nodes into the vector left right root
    if (root == nullptr)
        return;
    postOrder(root->left, nodes);
    postOrder(root->right, nodes);
    nodes.push_back(root);
}

void AVLTree::printInorder(Node *root) {
    // prints vector names
    vector<Node*> nodes;
    inOrder(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1) {
            cout << nodes[i]->name << ", ";
        } else {
            cout << nodes[i]->name;
        }
    }
}

void AVLTree::printPreorder(Node *root) {
    vector<Node*> nodes;
    preOrder(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1) {
            cout << nodes[i]->name << ", ";
        } else {
            cout << nodes[i]->name;
        }
    }
}

void AVLTree::printPostorder(Node *root) {
    vector<Node*> nodes;
    postOrder(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1)
            cout << nodes[i]->name << ", ";
        else
            cout << nodes[i]->name;

    }
}

void AVLTree::printLevel(Node *root) {
    // height of the root
    int levelCount = height(root);
    cout << levelCount << endl;
}

bool AVLTree::searchID(Node *root, int ID) {
    // if ID not found
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return false;
    }
    //find the unique ID, return true;
    if (root->ID == ID) {
        cout << root->name << endl;
        return true;
    }
    else if (ID > root->ID) {
        searchID(root->right, ID);
    }
    else if (ID < root->ID) {
        searchID(root->left, ID);
    }
}

bool AVLTree::ifIDExists(Node *root, int ID) {
    //check if ID exists
    if (root == nullptr) {
        return false;
    }
    if (root->ID == ID) {
        return true;
    }
    bool left = ifIDExists(root->left, ID);
    if (left)
        return true;
    //if not in the left subtree, then search in the right subtree
    bool right = ifIDExists(root->right, ID);
    return right;
}

bool AVLTree::searchName(Node *root, string name) {
    vector<Node*> nameMatch;
    vector<Node*> nodes;
    preOrder(root, nodes);

    for (auto & node : nodes){
        if (node->name == name){
            nameMatch.push_back(node);
            if(node->ID < 10000000){
                // syntax for 0s in ID
                cout << setw(8) << setfill('0') << node->ID << endl;
            } else {
                cout << node->ID << endl;
            }
        }

    }
    // name not found
    if(nameMatch.empty()){
        cout << "unsuccessful" << endl;
        return false;
    } else {
        return true;
    }
}

Node *AVLTree::leftMost(Node *node) {
    Node* temp = node;
    while(temp->left != nullptr)
        temp = temp->left;
    return temp;
}

Node *AVLTree::remove(Node *root, int ID) {
    if (root == nullptr){
        return nullptr;
    }

    if (ID > root->ID) {
        root->right = remove(root->right, ID);
    } else if (ID < root->ID) {
        root->left = remove(root->left, ID);
    } else {
        this->numNodes--;
        // no children in parent
        if (root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
            return root;
        }
            // only right children
        else if(root->left == nullptr){
            Node* temp = root;
            root = root->right;
            delete temp;
            return root;
        }
            // only left children
        else if(root->right == nullptr){
            Node* temp = root;
            root = root->left;
            delete temp;
            return root;
        }
            // is 2 children


        else{
            // copy the inorder successor's value to the root
            Node* temp = leftMost(root->right);
            root->ID = temp->ID;
            root->name = temp->name;
            // remove the duplicate from right subtree
            root->right = remove(root->right, root->ID);
            return root;
        }
    }
    return root;
}

Node *AVLTree::removeInorder(Node *root, int count) {
    // tree is empty
    if(root == nullptr)
    {
        cout << "unsuccessful" << endl;
        return root;
    }

    vector<Node*> nodes;
    inOrder(this->treeroot, nodes);
    // count is out of bounds
    if( count > nodes.size()-1)
    {
        cout << "unsuccessful" << endl;
        return root;
    }
    else{
        // remove function to remove node at position
        Node* temp = remove(this->treeroot, nodes[count]->ID);
        cout << "successful" << endl;
        return temp;
    }
}
