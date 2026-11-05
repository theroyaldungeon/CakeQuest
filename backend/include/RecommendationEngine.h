//
// Created by maldo on 11/2/2026.
//

#ifndef CAKEQUEST_RECOMMENDATIONENGINE_H
#define CAKEQUEST_RECOMMENDATIONENGINE_H

#include "Recipe.h"
#include "BTree.h"

#include <string>
#include <vector>

class RecommendationEngine {
public:

    static std::vector<Recipe>searchRecipes(const std::string& ingredient, BTree& tree, const std::vector<Recipe>& recipes);

    static std::vector<int>searchExactMatch(const std::vector<std::string>& ingredients, BTree& tree);

    static std::vector<std::pair<int,int>>searchRankedMatches(const std::vector<std::string>& ingredients, BTree& tree);
};

#endif