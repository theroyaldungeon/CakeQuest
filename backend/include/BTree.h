//
// Created by maldo on 11/2/2026.
//

#ifndef CAKEQUEST_BTREE_H
#define CAKEQUEST_BTREE_H

#include "IngredientEntry.h"

#include <string>
#include <vector>

class BTreeNode { // Represents single node inside BTree

public:
    std::vector<IngredientEntry> keys;
    std::vector<BTreeNode*> children;

    bool leaf;

    BTreeNode(bool leaf);
};

class BTree { // BTree used for ingredient indexing
private:
    BTreeNode* root;

public:
    BTree();

    void insert(std::string key);

    bool search(std::string key);
};

#endif