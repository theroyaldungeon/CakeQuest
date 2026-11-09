
#include "RecommendationEngine.h"
#include <unordered_map>
#include <algorithm>

std::vector<Recipe> RecommendationEngine::searchRecipes(
    const std::string& ingredient,
    BTree& tree,
    const std::vector<Recipe>& recipes
) {
    std::vector<Recipe> results;

    auto recipeIDs = tree.queryIngredient(ingredient);

    for (int id : recipeIDs) {
        if (id >= 0 && id < static_cast<int>(recipes.size())) {
            results.push_back(recipes[id]);
        }
    }

    return results;
}

std::vector<int> RecommendationEngine::searchExactMatch(
    const std::vector<std::string>& ingredients,
    BTree& tree
) {
    std::unordered_map<int, int> counts;

    for (const auto& ingredient : ingredients) {
        auto recipeIDs = tree.queryIngredient(ingredient);

        for (int id : recipeIDs) {
            counts[id]++;
        }
    }

    std::vector<int> matches;

    for (const auto& pair : counts) {
        if (pair.second == static_cast<int>(ingredients.size())) {
            matches.push_back(pair.first);
        }
    }

    return matches;
}

std::vector<std::pair<int, int>>
RecommendationEngine::searchRankedMatches(
    const std::vector<std::string>& ingredients,
    BTree& tree
) {
    std::unordered_map<int, int> counts;

    for (const auto& ingredient : ingredients) {
        auto recipeIDs = tree.queryIngredient(ingredient);

        for (int id : recipeIDs) {
            counts[id]++;
        }
    }

    std::vector<std::pair<int, int>> results;
    results.reserve(counts.size());

    for (const auto& pair : counts) {
        results.push_back(pair);
    }

    // Sorting is performed by main.cpp.
    return results;
}

std::vector<Recipe> RecommendationEngine::recommendRecipes(
    const std::vector<std::string>& ingredients,
    BTree& tree,
    const std::vector<Recipe>& recipes
) {
    auto rankedRecipes = searchRankedMatches(ingredients, tree);

    std::sort(
        rankedRecipes.begin(),
        rankedRecipes.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    std::vector<Recipe> results;
    results.reserve(rankedRecipes.size());

    for (const auto& pair : rankedRecipes) {
        if (pair.first >= 0 &&
            pair.first < static_cast<int>(recipes.size())) {
            results.push_back(recipes[pair.first]);
        }
    }

    return results;
}

std::vector<Recipe> RecommendationEngine::searchAllIngredients(
    const std::vector<std::string>& ingredients,
    BTree& tree,
    const std::vector<Recipe>& recipes
) {
    std::vector<int> ids = searchExactMatch(ingredients, tree);

    std::vector<Recipe> results;
    results.reserve(ids.size());

    for (int id : ids) {
        if (id >= 0 && id < static_cast<int>(recipes.size())) {
            results.push_back(recipes[id]);
        }
    }

    return results;
}
