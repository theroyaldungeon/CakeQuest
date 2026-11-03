//
// Created by maldo on 11/2/2026.
//

#include "../include/BTree.h"
#include <iostream>

int main() {
    BTree tree;

    tree.insert("milk");
    tree.insert("eggs");
    tree.insert("flour");

    std::cout << std::boolalpha;

    std::cout << "Contains milk: " << tree.search("milk") << std::endl;

    std::cout << "Contains sugar: " << tree.search("sugar") << std::endl;

    return 0;
}