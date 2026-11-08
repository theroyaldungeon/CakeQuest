//
// Created by maldo on 11/4/2026.
//edited by St Lot
//

#include "IngredientIndexBuilder.h"

#include <unordered_map>
#include <cctype>
#include <algorithm>

void IngredientIndexBuilder::buildIndex(const std::vector<Recipe>& recipes, BTree& tree) {
    std::unordered_map<std::string, std::vector<int>> ingredientMap;

    for (const auto& recipe : recipes) {
        for (const auto& ingredient : recipe.ingredients) {
            
            //making sure the its only in lower case, flour vs Flour
            std::string lowerOnly = ingredient;
            std::transform(lowerOnly.begin(), lowerOnly.end(), lowerOnly.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c));});
            
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