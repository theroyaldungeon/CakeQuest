
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_set>

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

    // Load recipes once.
    std::vector<Recipe> recipes =
        RecipeLoader::loadRecipes(filename);

    if (recipes.empty()) {
        std::cerr << "Failed to load recipes." << std::endl;
        return 1;
    }

    // Build both indexes once.
    BTree tree;
    IngredientIndexBuilder::buildIndex(recipes, tree);

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

            // Normalize and remove duplicate ingredients.
            std::unordered_set<std::string> uniqueIngredients;
            std::vector<std::string> normalizedIngredients;

            normalizedIngredients.reserve(ingredients.size());

            for (std::string ingredient : ingredients) {

                std::transform(
                    ingredient.begin(),
                    ingredient.end(),
                    ingredient.begin(),
                    [](unsigned char c) {
                        return static_cast<char>(std::tolower(c));
                    }
                );

                if (!ingredient.empty() &&
                    uniqueIngredients.insert(ingredient).second) {

                    normalizedIngredients.push_back(ingredient);
                }
            }

            if (normalizedIngredients.empty()) {
                throw std::runtime_error(
                    "Please provide valid ingredients."
                );
            }

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
                            normalizedIngredients, hashIndex
                        );

                } else {

                    matches =
                        RecommendationEngine::searchExactMatch(
                            normalizedIngredients, tree
                        );
                }

                // Sort exact matches by preparation time.
                MinHeap timeHeap;

                for (int id : matches) {

                    if (id >= 0 &&
                        id < static_cast<int>(recipes.size())) {

                        timeHeap.insert(
                            id,
                            calculateTime(recipes[id])
                        );
                    }
                }

                sortedMatches = timeHeap.heapSort();

            }

            // PARTIAL INGREDIENT MATCHING
            else {

                std::vector<std::pair<int, int>> rankedMatches;

                if (searchMethod == "hash") {

                    rankedMatches =
                        HashRecommendationEngine::searchRankedMatches(
                            normalizedIngredients, hashIndex
                        );

                } else {

                    rankedMatches =
                        RecommendationEngine::searchRankedMatches(
                            normalizedIngredients, tree
                        );
                }

                // Sort by matching ingredient count.
                std::stable_sort(
                    rankedMatches.begin(),
                    rankedMatches.end(),
                    [](const auto& a, const auto& b) {
                        return a.second > b.second;
                    }
                );

                sortedMatches.reserve(rankedMatches.size());

                for (const auto& match : rankedMatches) {

                    if (match.first >= 0 &&
                        match.first < static_cast<int>(recipes.size())) {

                        sortedMatches.push_back(match.first);
                    }
                }
            }

            // LIMIT RESULTS TO 100 RECIPES.
            const size_t MAX_RESULTS = 100;

            if (sortedMatches.size() > MAX_RESULTS) {
                sortedMatches.resize(MAX_RESULTS);
            }

            // Build JSON response.
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

            // stdout is reserved for JSON responses.
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
