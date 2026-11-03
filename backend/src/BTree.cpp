//
// Created by maldo on 11/2/2026.
//

#include "BTree.h"

BTreeNode::BTreeNode(bool leaf) { // Create node and check if it's a leaf node
    this->leaf = leaf;
}

BTree::BTree() { // Create empty tree
    root = nullptr;
}

void BTree::insert(std::string key) { // insertion method placehldr
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys.push_back(key);
    }
}

bool BTree::search(std::string key) { // search method placehldr
    if (root == nullptr) {
        return false;
    }

    for (const std::string& currentKey : root->keys) {
        if (currentKey == key) {
            return true;
        }
    }
    return false;
}