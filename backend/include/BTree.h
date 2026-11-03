//
// Created by maldo on 11/2/2026.
//

#ifndef BAKINGBAD_BTREE_H
#define BAKINGBAD_BTREE_H

#include <string>
#include <vector>

class BTreeNode { // Represents single node inside BTree

public:
    std::vector<std::string> keys;
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

#endif //BAKINGBAD_BTREE_H