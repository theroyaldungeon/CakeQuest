//
// Created by rspin on 11/7/2026.
//
#ifndef CAKEQUEST_HASHINDEXBUILDER_H
#define CAKEQUEST_HASHINDEXBUILDER_H

#include "Recipe.h"
#include "HashIndex.h"

#include <vector>

// Hash-index counterpart of IngredientIndexBuilder.
class HashIndexBuilder {
public:
    static void buildIndex(const std::vector<Recipe>& recipes, HashIndex& index);
};

#endif