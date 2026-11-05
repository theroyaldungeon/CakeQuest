//
// Created by maldo on 11/4/2026.
//

#include "RecipeLoader.h"
#include "IngredientIndexBuilder.h"

#include <iostream>
#include <chrono>
#include <vector>

void displayRecipes(const std::string& ingredient, BTree& tree, const std::vector<Recipe>& recipes) {
    auto recipeIDs = tree.queryIngredient(ingredient);

    std::cout << "\nRecipes containing " << ingredient << ":\n";

    for(int id : recipeIDs) {
        std::cout << recipes[id].title << std::endl;
    }
}

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

    displayRecipes(
    "milk",
    tree,
    recipes
);

    displayRecipes(
        "butter",
        tree,
        recipes
    );

    displayRecipes(
        "vanilla",
        tree,
        recipes
    );

    displayRecipes(
    "vanilla",
    tree,
    recipes
);

    std::cout
        << "\n========== BENCHMARKS ==========\n";

    std::vector<std::string> benchmarkTests =
    {
        "milk",
        "butter",
        "sugar",
        "flour",
        "vanilla",
        "chocolate",
        "egg",
        "cream"
    };

    for(const auto& ingredient : benchmarkTests) {
        const int NUM_SEARCHES = 1000;

        auto start = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < NUM_SEARCHES; i++) {
            tree.search(ingredient);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << ingredient << ": " << duration.count() << " us" << std::endl;

        duration.count() / static_cast<double>(NUM_SEARCHES);
    }

    return 0;
}