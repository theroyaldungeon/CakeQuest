//
// Created by maldo on 11/5/2026.
//

#include "RecipeLoader.h"
#include "IngredientIndexBuilder.h"
#include "RecommendationEngine.h"

#include <iostream>

int main()
{
    auto recipes =
        RecipeLoader::loadRecipes(
            "data/cleaned/sample_recipes.json"
        );

    BTree tree;

    IngredientIndexBuilder::buildIndex(
        recipes,
        tree
    );

    std::vector<std::string> ingredients =
    {
        "milk",
        "butter",
        "sugar"
    };

    auto results =
        RecommendationEngine
            ::recommendRecipes(
                ingredients,
                tree,
                recipes
            );

    std::cout << "Results:\n";

    for(size_t i = 0;
        i < std::min<size_t>(10, results.size());
        i++)
    {
        std::cout
            << results[i].title
            << std::endl;
    }

    return 0;
}