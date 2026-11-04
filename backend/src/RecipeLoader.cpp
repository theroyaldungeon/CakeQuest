//
// Created by maldo on 11/2/2026.
//

#include "RecipeLoader.h"
#include "C:/Users/maldo/CLionProjects/BakingBad/external/json.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

std::vector<Recipe>
RecipeLoader::loadRecipes(const std::string& filename) {
    std::vector<Recipe> recipes;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open file."
                  << std::endl;

        return recipes;
    }

    json data;

    file >> data;

    for (size_t i = 0; i < data.size(); i++) {
        Recipe recipe;

        recipe.id = static_cast<int>(i);

        recipe.title =
            data[i]["title"];

        recipes.push_back(recipe);
    }

    return recipes;
}