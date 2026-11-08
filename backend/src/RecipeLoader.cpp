//
// Created by maldo on 11/2/2026.
//

#include "RecipeLoader.h"
#include "json.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

std::vector<Recipe>
RecipeLoader::loadRecipes(const std::string& filename) {
    std::vector<Recipe> recipes;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open file." << std::endl;

        return recipes;
    }

    json data;
    file >> data;

    for (size_t i = 0; i < data.size(); i++) {
        Recipe recipe;

        recipe.id = static_cast<int>(i);

        recipe.title = data[i]["title"];
        recipe.link = data[i]["link"];
        recipe.source = data[i]["source"];
        recipe.site = data[i]["site"];

        json nerIngredients = json::parse(data[i]["NER"].get<std::string>());

        for (auto& ingredient : nerIngredients) {
            recipe.ingredients.push_back(ingredient.get<std::string>());
        }

        json parsedDirections = json::parse(data[i]["directions"].get<std::string>());

        for (auto& direction : parsedDirections) {
            recipe.directions.push_back(direction.get<std::string>());
        }

        recipes.push_back(recipe);
    }

    return recipes;
}