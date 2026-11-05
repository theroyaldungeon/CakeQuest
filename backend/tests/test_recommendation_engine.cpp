//
// Created by maldo on 11/5/2026.
//

#include "RecipeLoader.h"
#include "IngredientIndexBuilder.h"
#include "RecommendationEngine.h"

#include <iostream>

int main() {
    auto recipes =
        RecipeLoader::loadRecipes("C:/Users/maldo/CLionProjects/BakingBad/data/cleaned/sample_recipes.json");

    BTree tree;

    IngredientIndexBuilder::buildIndex(recipes, tree);

    auto results = RecommendationEngine::searchRecipes("milk", tree, recipes);

    std::cout << "Results Found: " << results.size() << std::endl;

    for(const auto& recipe : results) {
        std::cout << recipe.title << std::endl;
    }

    std::vector<std::string> ingredients = {
        "milk",
        "butter",
        "sugar",
        "chocolate"
    };

    auto exactMatches = RecommendationEngine::searchExactMatch(ingredients,tree);

    std::cout << "Exact Matches:\n";

    for(int id : exactMatches) {
        std::cout << recipes[id].title << std::endl;
    }

    auto rankedMatches =
    RecommendationEngine::searchRankedMatches(ingredients, tree);

    std::cout << "\nTop Ranked:\n";

    for(int i = 0; i < 10 && i < rankedMatches.size(); i++) {
        std::cout << recipes[rankedMatches[i].first].title << " (" << rankedMatches[i].second << " ingredients)\n";
    }

    return 0;
}