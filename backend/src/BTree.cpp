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
        return;
        }

        if(root->keys.size() == 2 * BTreeNode::T - 1) {
            BTreeNode* newRoot = new BTreeNode(false);

            newRoot->children.push_back(root);

            newRoot->splitChild(0, root);

            root = newRoot;
    }

    root->insertNonFull(entry);
}

IngredientEntry* BTree::search(const std::string& ingredient) { // search method
    return searchHelper(root,ingredient);
}

IngredientEntry* BTree::searchHelper(BTreeNode* node, const std::string& ingredient) {
    if(node == nullptr) {
        return nullptr;
    }

    int i = 0;

    while(i < node->keys.size() && ingredient > node->keys[i].ingredient) {
        i++;
    }

    if(i < node->keys.size() && node->keys[i].ingredient == ingredient) {
        return &node->keys[i];
    }

    if(node->leaf) {
        return nullptr;
    }

    return searchHelper(node->children[i], ingredient);
}

void BTreeNode::insertNonFull(const IngredientEntry& entry) {
    int i = static_cast<int>(keys.size()) -1;

    if(leaf) {
        keys.push_back(entry);

        while(i >= 0 && keys[i].ingredient > entry.ingredient) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = entry;
    }

    else {
        while(i >= 0 && keys[i].ingredient > entry.ingredient) {
            i--;
        }

        i++;

        if(children[i]->keys.size() == 2 * T - 1) {
            splitChild(i, children[i]);

            if(keys[i].ingredient < entry.ingredient) {
                i++;
            }
        }

        children[i]->insertNonFull(entry);
    }
}

void BTreeNode::splitChild(int index, BTreeNode* child) {
    BTreeNode* newNode = new BTreeNode(child->leaf);

    for (int j = 0; j < T - 1; j++) { // move upper half of keys
        newNode->keys.push_back(child->keys[j + T]);
    }

    if (!child->leaf) { // move children if not leaf
        for (int j = 0; j < T; j++) {
            newNode->children.push_back(child->children[j + T]);
        }
    }

    IngredientEntry median = child->keys[T-1];

    child->keys.resize(T- 1);

    if (!child->leaf) {
        child->children.resize(T);
    }

    children.insert(children.begin() + index + 1, newNode);

    keys.insert(keys.begin() + index, median);
}

