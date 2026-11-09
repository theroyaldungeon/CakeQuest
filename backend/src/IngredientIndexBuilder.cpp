//
// Created by maldo on 11/4/2026.
<<<<<<< HEAD
=======
//edited by St Lot
>>>>>>> temp-Connection-of-Front-end-to-backened,-still-minor-filtering-errors
//

#include "IngredientIndexBuilder.h"

#include <unordered_map>
<<<<<<< HEAD
=======
#include <cctype>
#include <algorithm>
>>>>>>> temp-Connection-of-Front-end-to-backened,-still-minor-filtering-errors

void IngredientIndexBuilder::buildIndex(const std::vector<Recipe>& recipes, BTree& tree) {
    std::unordered_map<std::string, std::vector<int>> ingredientMap;

    for (const auto& recipe : recipes) {
        for (const auto& ingredient : recipe.ingredients) {
<<<<<<< HEAD
=======
            
            //making sure the its only in lower case, flour vs Flour
            std::string lowerOnly = ingredient;
            std::transform(lowerOnly.begin(), lowerOnly.end(), lowerOnly.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c));});
            
>>>>>>> temp-Connection-of-Front-end-to-backened,-still-minor-filtering-errors
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