//
// Created by maldo on 11/5/2026.
//

#include "RecipeLoader.h"
#include "IngredientIndexBuilder.h"
#include "RecommendationEngine.h"

#include <iostream>

int main() {
    auto recipes = RecipeLoader::loadRecipes("C:/Users/maldo/CLionProjects/BakingBad/data/cleaned/200k.json");

    BTree tree;

    IngredientIndexBuilder::buildIndex(recipes, tree);

    std::cout<< "\n========== SINGLE INGREDIENT ==========\n";
    auto searchResults = RecommendationEngine::searchRecipes("milk", tree, recipes);

    std::cout << "Results Found: " << searchResults.size() << std::endl;

    for(size_t i = 0; i < std::min<size_t>(10, searchResults.size()); i++) {
        std::cout << searchResults[i].title << std::endl;
    }

    std::cout<< "\n========== EXACT MATCH ==========\n";

    std::vector<std::string> ingredients = {
        "milk",
        "butter",
        "sugar",
        "chocolate"
    };

    auto exactMatches = RecommendationEngine::searchExactMatch(ingredients,tree);

    std::cout << "Exact Matches:\n" << exactMatches.size() << std::endl;

    for(size_t i = 0; i < std::min<size_t>(10, exactMatches.size()); i++) {
        std::cout << recipes[exactMatches[i]].title << std::endl;
    }

    std::cout << "\n========== RANKED MATCH ==========\n";
    auto rankedMatches =
    RecommendationEngine::searchRankedMatches(ingredients, tree);

    std::cout << "\nRanked Matches:\n" << rankedMatches.size() << std::endl;

    for(int i = 0; i < 10 && i < rankedMatches.size(); i++) {
        std::cout << recipes[rankedMatches[i].first].title << " (" << rankedMatches[i].second << " matches)\n";
    }

    std::cout << "\n========== RECOMMENDED RECIPES ==========\n";
    auto results = RecommendationEngine::recommendRecipes(ingredients, tree, recipes);

    std::cout << "Recommended Recipes: " << results.size() << std::endl;

    for(size_t i = 0; i < std::min<size_t>(10, results.size()); i++) {
        std::cout << results[i].title << std::endl;
    }

    return 0;
}