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

    auto result = tree.search("milk");

    if (result != nullptr) {
        std::cout << "Ingredient: " << result->ingredient << std::endl;

        std::cout << "Recipes Found: " << result->recipeIDs.size() << std::endl;
     }

    return 0;
}