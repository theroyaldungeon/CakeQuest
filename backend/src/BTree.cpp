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

void BTree::insert(const IngredientEntry& entry) { // insertion method
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys.push_back(entry);
    }
}

IngredientEntry* BTree::search(const std::string& ingredient) { // search method
    if (root == nullptr) {
        return nullptr;;
    }

    for (auto& entry : root->keys) {
        if (entry.ingredient == ingredient) {
            return &entry;
        }
    }
    return nullptr;
}