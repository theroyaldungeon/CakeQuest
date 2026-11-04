//
// Created by maldo on 11/4/2026.
//

#ifndef CAKEQUEST_INGREDIENTINDEXBUILDER_H
#define CAKEQUEST_INGREDIENTINDEXBUILDER_H

#include "Recipe.h"
#include "BTree.h"

class IngredientIndexBuilder {
public:

    static void buildIndex(
        const std::vector<Recipe>& recipes,
        BTree& tree
    );
};

#endif