
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "RecipeLoader.h"
#include "IngredientIndexBuilder.h"
#include "RecommendationEngine.h"
#include "BTree.h"
#include "json.hpp"
#include "MinHeap.h"

using json = nlohmann::json;

int main(int argc, char* argv[]) {

    // Path for whatever computer
    std::string filename = (argc > 1)
        ? argv[1]
        : "data/cleaned/200k.json";

    // Load recipes
    std::vector<Recipe> recipes = RecipeLoader::loadRecipes(filename);

    if (recipes.empty()) {
        std::cerr << "Failed to load recipes." << std::endl;
        return 1;
    }

    // Build B-tree
    BTree tree;
    IngredientIndexBuilder::buildIndex(recipes, tree);

    std::cerr << "Loaded " << recipes.size()
              << " recipes. B-tree ready." << std::endl;

    // Search requests
    std::string line;

    while (std::getline(std::cin, line)) {

        try {

            json request = json::parse(line);

            std::vector<std::string> ingredients =
                request.at("ingredients").get<std::vector<std::string>>();

            // Normalize user input
            for (std::string& ingredient : ingredients) {
                std::transform(
                    ingredient.begin(),
                    ingredient.end(),
                    ingredient.begin(),
                    [](unsigned char c) {
                        return static_cast<char>(std::tolower(c));
                    }
                );
            }

            // Read filter selection
            bool allIngredients =
                request.value("allIngredients", false);

            std::vector<int> sortedMatches;

            if (allIngredients) {

                // Exact matches, sorted by prep time
                std::vector<int> matches =
                    RecommendationEngine::searchExactMatch(
                        ingredients, tree
                    );

                MinHeap timeHeap;

                for (int id : matches) {
                    timeHeap.insert(id, calculateTime(recipes[id]));
                }

                sortedMatches = timeHeap.heapSort();

            }
            else {

                // Partial matches, ranked by ingredient count
                auto rankedMatches =
                    RecommendationEngine::searchRankedMatches(
                        ingredients, tree
                    );

                // Highest ingredient match count first.
                // Equal counts retain their existing relative order.
                std::stable_sort(
                    rankedMatches.begin(),
                    rankedMatches.end(),
                    [](const auto& a, const auto& b) {
                        return a.second > b.second;
                    }
                );

                for (const auto& match : rankedMatches) {
                    sortedMatches.push_back(match.first);
                }
            }

            // Build JSON results
            json results = json::array();

            for (int id : sortedMatches) {

                const Recipe& recipe = recipes[id];

                results.push_back({
                    {"id", recipe.id},
                    {"title", recipe.title},
                    {"link", recipe.link},
                    {"source", recipe.source},
                    {"site", recipe.site},
                    {"ingredients", recipe.ingredients},
                    {"directions", recipe.directions},
                    {"prepTime", calculateTime(recipe)}
                });
            }

            // stdout is reserved for JSON responses
            std::cout << json{{"recipes", results}}.dump()
                      << std::endl;

        }
        catch (const std::exception& e) {

            std::cout << json{
                {"error", e.what()}
            }.dump() << std::endl;
        }
    }

    return 0;
}
