//
// Created by maldo on 11/4/2026.
//

#include "IngredientIndexBuilder.h"

#include <unordered_map>

void IngredientIndexBuilder::buildIndex(const std::vector<Recipe>& recipes, BTree& tree) {
    std::unordered_map<std::string, std::vector<int>> ingredientMap;

    for (const auto& recipe : recipes) {
        for (const auto& ingredient : recipe.ingredients) {
            ingredientMap[ingredient].push_back(recipe.id);
        }
    }

    for (const auto& pair : ingredientMap) {
        IngredientEntry entry;
        entry.ingredient = pair.first;
        entry.recipeIDs = pair.second;

        tree.insert(entry);
    }
}