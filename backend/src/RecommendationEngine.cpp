//
// Created by maldo on 11/2/2026.
//

#include "RecommendationEngine.h"
#include <unordered_map>
#include <algorithm>

std::vector<Recipe> RecommendationEngine::searchRecipes(const std::string& ingredient, BTree& tree, const std::vector<Recipe>& recipes) {
    std::vector<Recipe> results;

    auto recipeIDs = tree.queryIngredient(ingredient);

    for(int id : recipeIDs) {
        results.push_back(recipes[id]);
    }

    return results;
}

std::vector<int> RecommendationEngine::searchExactMatch(const std::vector<std::string>& ingredients, BTree& tree) {
    std::unordered_map<int, int> counts;

    for(const auto& ingredient : ingredients) {
        auto recipeIDs = tree.queryIngredient(ingredient);

        for(int id : recipeIDs) {
            counts[id]++;
        }
    }

    std::vector<int> matches;

    for(const auto& pair : counts) {
        if(pair.second == ingredients.size()) {
            matches.push_back(pair.first);
        }
    }

    return matches;
}

std::vector<std::pair<int,int>> RecommendationEngine::searchRankedMatches(const std::vector<std::string>& ingredients, BTree& tree) {
    std::unordered_map<int,int> counts;

    for(const auto& ingredient : ingredients) {
        auto recipeIDs = tree.queryIngredient(ingredient);

        for(int id : recipeIDs) {
            counts[id]++;
        }
    }
<<<<<<< HEAD
=======
    
>>>>>>> temp-Connection-of-Front-end-to-backened,-still-minor-filtering-errors

    std::vector<std::pair<int,int>> results;

    for(const auto& pair : counts) {
        results.push_back(pair);
    }

    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    return results;
}

std::vector<Recipe>
RecommendationEngine::recommendRecipes(const std::vector<std::string>& ingredients, BTree& tree, const std::vector<Recipe>& recipes) {
    std::unordered_map<int,int> counts;

    for(const auto& ingredient : ingredients) {
        auto ids = tree.queryIngredient(ingredient);

        for(int id : ids) {
            counts[id]++;
        }
    }

    std::vector<std::pair<int,int>> rankedRecipes;

    for(const auto& pair : counts) {
        rankedRecipes.push_back(pair);
    }

    std::sort(rankedRecipes.begin(), rankedRecipes.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    std::vector<Recipe> results;

    for(const auto& pair : rankedRecipes) {
        results.push_back(recipes[pair.first]
        );
    }

    return results;
<<<<<<< HEAD
=======
}

std::vector<Recipe> RecommendationEngine::searchAllIngredients(
    const std::vector<std::string>& ingredients,
    BTree& tree,
    const std::vector<Recipe>& recipes
) {
    std::vector<int> ids = searchExactMatch(ingredients, tree);

    std::vector<Recipe> results;

    for (int id : ids) {
        if (id >= 0 && id < recipes.size()) {
            results.push_back(recipes[id]);
        }
    }

    return results;
>>>>>>> temp-Connection-of-Front-end-to-backened,-still-minor-filtering-errors
}