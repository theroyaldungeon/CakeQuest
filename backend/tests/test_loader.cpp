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
        << "Recipes Loaded: "
        << recipes.size()
        << std::endl;

    return 0;
}