//
// Created by maldo on 11/2/2026.
//

#include "BTree.h"
#include <iostream>

int main() {
    BTree tree;

    IngredientEntry milk;

    milk.ingredient = "milk";

    milk.recipeIDs.push_back(1);

    tree.insert(milk);

    IngredientEntry* result = tree.search("milk");

    if(result != nullptr) {
        std::cout << result->ingredient << std::endl;
    }

    return 0;
}