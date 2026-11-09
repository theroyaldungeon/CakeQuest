
//
// Created by rspin on 11/7/2026.
//
#include "HashIndexBuilder.h"

#include <algorithm>
#include <cctype>

void HashIndexBuilder::buildIndex(const std::vector<Recipe>& recipes, HashIndex& index) {
    for (const auto& recipe : recipes) {
        for (const auto& ingredient : recipe.ingredients) {

            // Make sure ingredients are lowercase for consistent searching.
            std::string lowerOnly = ingredient;

            std::transform(
                lowerOnly.begin(),
                lowerOnly.end(),
                lowerOnly.begin(),
                [](unsigned char c) {
                    return static_cast<char>(std::tolower(c));
                }
            );

            index.add(lowerOnly, recipe.id);
        }
    }
}
