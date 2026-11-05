//
// Created by maldo on 11/4/2026.
//

#include "RecipeLoader.h"
#include "IngredientIndexBuilder.h"

#include <iostream>
#include <chrono>

int main() {
    auto recipes = RecipeLoader::loadRecipes("C:/Users/maldo/CLionProjects/BakingBad/data/cleaned/sample_recipes.json");

    BTree tree;

    IngredientIndexBuilder::buildIndex(recipes, tree);

    std::cout << "\nIngredient Traversal:\n" << std::endl;
    tree.traverse();

    std::vector<std::string> tests =
    {
        "milk",
        "butter",
        "sugar",
        "vanilla",
        "watermelon"
    };

    for (const auto& ingredient : tests) {
        auto result = tree.search(ingredient);

        if (result != nullptr) {
            std::cout << "Ingredient: " << result->ingredient << std::endl;

            std::cout << "Recipes Found: " << result->recipeIDs.size() << std::endl;
        }
        else {
            std::cout << ingredient << " -> not found" << std::endl;
        }
    }


    std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    auto searchResult = tree.search("milk");

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\nSearch took " << duration.count() << " microseconds" << std::endl;

    if(searchResult != nullptr) {
        std::cout
            << "Timing Search Found: "
            << searchResult->ingredient
            << std::endl;
    }

    auto milkRecipes = tree.queryIngredient("milk");

    std::cout << "\nMilk Recipe IDs:\n";

    for(int id : milkRecipes) {
        std::cout << id << " ";
    }

    std::cout << std::endl;

    std::cout << "\nRecipes containing milk:\n";

    for(int id : milkRecipes) {
        std::cout << recipes[id].title << std::endl;
    }

    return 0;
}