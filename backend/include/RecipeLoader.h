//
// Created by maldo on 11/2/2026.
//

#ifndef CAKEQUEST_RECIPELOADER_H
#define CAKEQUEST_RECIPELOADER_H

#include "Recipe.h"

#include <string>
#include <vector>

class RecipeLoader {
    public:

        static std::vector<Recipe>
        loadRecipes(const std::string& filename);
};

#endif