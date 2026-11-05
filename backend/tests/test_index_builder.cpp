//
// Created by maldo on 11/4/2026.
//

#include "RecipeLoader.h"
#include "IngredientIndexBuilder.h"

#include <iostream>

int main() {
    auto recipes = RecipeLoader::loadRecipes("C:/Users/maldo/CLionProjects/BakingBad/data/cleaned/sample_recipes.json");

    BTree tree;

    IngredientIndexBuilder::buildIndex(recipes, tree);

    std::cout << "\nIngredient Traversal:\n" << std::endl;
    tree.traverse();

    std::vector<std::string> tests =
    {
        "milk",
        "butter",
        "sugar",
        "vanilla",
        "watermelon"
    };

    for (const auto& ingredient : tests) {
        auto result = tree.search(ingredient);

        if (result != nullptr) {
            std::cout << "Ingredient: " << result->ingredient << std::endl;

            std::cout << "Recipes Found: " << result->recipeIDs.size() << std::endl;
        }

        else {
            std::cout << ingredient << " -> not found" << std::endl;
        }
    }

    return 0;
}