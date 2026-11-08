#ifndef CAKEQUEST_HASHRECOMMENDATIONENGINE_H
#define CAKEQUEST_HASHRECOMMENDATIONENGINE_H

#include "Recipe.h"
#include "HashIndex.h"

#include <string>
#include <utility>
#include <vector>

// Hash-index counterpart of RecommendationEngine.
// Same logic and same results as the B-tree version; only the index differs.
class HashRecommendationEngine {
public:

    static std::vector<Recipe> searchRecipes(const std::string& ingredient, HashIndex& index, const std::vector<Recipe>& recipes);

    static std::vector<int> searchExactMatch(const std::vector<std::string>& ingredients, HashIndex& index);

    static std::vector<std::pair<int,int>> searchRankedMatches(const std::vector<std::string>& ingredients, HashIndex& index);

    static std::vector<Recipe> recommendRecipes(const std::vector<std::string>& ingredients, HashIndex& index, const std::vector<Recipe>& recipes);
};

#endif