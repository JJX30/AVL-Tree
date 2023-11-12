//
// Created by Mauricio Del Castillo on 2/17/23.
//

#include "Node.h"

#include <utility>

Node::Node(string name, int ID) {
    this->name = std::move(name);
    this->ID = ID;
    this->right = nullptr;
    this->left = nullptr;
}
