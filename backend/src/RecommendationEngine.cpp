//
// Created by maldo on 11/2/2026.
//

#include "RecommendationEngine.h"

std::vector<int>RecommendationEngine::searchByIngredient(const std::string& ingredient, BTree& tree) {
    return tree.queryIngredient(ingredient);
}