
#include "HashRecommendationEngine.h"

#include <algorithm>
#include <unordered_map>

std::vector<Recipe> HashRecommendationEngine::searchRecipes(
    const std::string& ingredient,
    HashIndex& index,
    const std::vector<Recipe>& recipes
) {
    std::vector<Recipe> results;

    auto recipeIDs = index.queryIngredient(ingredient);

    for (int id : recipeIDs) {
        if (id >= 0 && id < static_cast<int>(recipes.size())) {
            results.push_back(recipes[id]);
        }
    }

    return results;
}

std::vector<int> HashRecommendationEngine::searchExactMatch(
    const std::vector<std::string>& ingredients,
    HashIndex& index
) {
    std::unordered_map<int, int> counts;

    for (const auto& ingredient : ingredients) {
        auto recipeIDs = index.queryIngredient(ingredient);

        for (int id : recipeIDs) {
            counts[id]++;
        }
    }

    std::vector<int> matches;
    matches.reserve(counts.size());

    for (const auto& pair : counts) {
        if (pair.second == static_cast<int>(ingredients.size())) {
            matches.push_back(pair.first);
        }
    }

    return matches;
}

std::vector<std::pair<int, int>>
HashRecommendationEngine::searchRankedMatches(
    const std::vector<std::string>& ingredients,
    HashIndex& index
) {
    std::unordered_map<int, int> counts;

    for (const auto& ingredient : ingredients) {
        auto recipeIDs = index.queryIngredient(ingredient);

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

std::vector<Recipe> HashRecommendationEngine::recommendRecipes(
    const std::vector<std::string>& ingredients,
    HashIndex& index,
    const std::vector<Recipe>& recipes
) {
    auto ranked = searchRankedMatches(ingredients, index);

    std::sort(
        ranked.begin(),
        ranked.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    std::vector<Recipe> results;
    results.reserve(ranked.size());

    for (const auto& pair : ranked) {
        if (pair.first >= 0 &&
            pair.first < static_cast<int>(recipes.size())) {
            results.push_back(recipes[pair.first]);
        }
    }

    return results;
}
