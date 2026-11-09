
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "RecipeLoader.h"
#include "IngredientIndexBuilder.h"
#include "RecommendationEngine.h"
#include "BTree.h"
#include "HashIndex.h"
#include "HashIndexBuilder.h"
#include "HashRecommendationEngine.h"
#include "json.hpp"
#include "MinHeap.h"

using json = nlohmann::json;

int main(int argc, char* argv[]) {

    std::string filename = (argc > 1)
        ? argv[1]
        : "data/cleaned/200k.json";

    // Load recipes
    std::vector<Recipe> recipes =
        RecipeLoader::loadRecipes(filename);

    if (recipes.empty()) {
        std::cerr << "Failed to load recipes." << std::endl;
        return 1;
    }

    // Build B-tree index
    BTree tree;
    IngredientIndexBuilder::buildIndex(recipes, tree);

    // Build Hash index
    HashIndex hashIndex;
    HashIndexBuilder::buildIndex(recipes, hashIndex);

    std::cerr << "Loaded " << recipes.size()
              << " recipes. Both indexes ready." << std::endl;

    std::string line;

    while (std::getline(std::cin, line)) {

        try {

            json request = json::parse(line);

            std::vector<std::string> ingredients =
                request.at("ingredients")
                    .get<std::vector<std::string>>();

            // Normalize ingredients
            for (std::string& ingredient : ingredients) {

                std::transform(
                    ingredient.begin(),
                    ingredient.end(),
                    ingredient.begin(),
                    [](unsigned char c) {
                        return static_cast<char>(
                            std::tolower(c)
                        );
                    }
                );
            }

            // Read frontend selections
            bool allIngredients =
                request.value("allIngredients", false);

            std::string searchMethod =
                request.value("searchMethod", "btree");

            if (searchMethod != "btree" &&
                searchMethod != "hash") {

                throw std::runtime_error(
                    "Invalid search method."
                );
            }

            std::vector<int> sortedMatches;

            // ALL INGREDIENTS FILTER
            if (allIngredients) {

                std::vector<int> matches;

                if (searchMethod == "hash") {

                    matches =
                        HashRecommendationEngine::searchExactMatch(
                            ingredients, hashIndex
                        );

                } else {

                    matches =
                        RecommendationEngine::searchExactMatch(
                            ingredients, tree
                        );
                }

                // Sort exact matches by prep time
                MinHeap timeHeap;

                for (int id : matches) {
                    timeHeap.insert(
                        id,
                        calculateTime(recipes[id])
                    );
                }

                sortedMatches = timeHeap.heapSort();

            }

            // PARTIAL INGREDIENT MATCHING
            else {

                std::vector<std::pair<int, int>> rankedMatches;

                if (searchMethod == "hash") {

                    rankedMatches =
                        HashRecommendationEngine::searchRankedMatches(
                            ingredients, hashIndex
                        );

                } else {

                    rankedMatches =
                        RecommendationEngine::searchRankedMatches(
                            ingredients, tree
                        );
                }

                // Sort by matching ingredient count.
                // Preserve the engine's order for ties.
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

            // Build JSON response
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

            // stdout reserved for JSON
            std::cout
                << json{{"recipes", results}}.dump()
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
