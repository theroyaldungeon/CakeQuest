//
// Created by rspin on 11/7/2026.
//
#include "HashIndexBuilder.h"

void HashIndexBuilder::buildIndex(const std::vector<Recipe>& recipes, HashIndex& index) {
    for (const auto& recipe : recipes) {
        for (const auto& ingredient : recipe.ingredients) {
            index.add(ingredient, recipe.id);
        }
    }
}
