//
// Created by maldo on 11/4/2026.
//

#ifndef CAKEQUEST_INGREDIENTENTRY_H
#define CAKEQUEST_INGREDIENTENTRY_H

#include <string>
#include <vector>

struct IngredientEntry {
    std::string ingredient;
    std::vector<int> recipeIDs;
};

#endif