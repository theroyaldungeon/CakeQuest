//
// Created by maldo on 11/3/2026.
//

#include "RecipeLoader.h"

#include <iostream>

int main() {
    auto recipes =
        RecipeLoader::loadRecipes(
            "C:/Users/maldo/CLionProjects/BakingBad/data/cleaned/sample_recipes.json"
        );

    std::cout
        << "Recipes Loaded: " << recipes.size() << std::endl;

    if (!recipes.empty()) {
        std::cout << "Title: " << recipes[0].title << std::endl;

        std::cout << "Ingredients: " << recipes[0].ingredients.size() << std::endl;

        std::cout << "Directions: " << recipes[0].directions.size() << std::endl;
    }
    return 0;
}