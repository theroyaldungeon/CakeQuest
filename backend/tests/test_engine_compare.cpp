// Checks that the B-tree engine and the hash engine agree on every query.
// Ties are compared after sorting by recipe ID, because the original engine
// leaves the order of equal counts unspecified.
#include "BTree.h"
#include "HashIndex.h"
#include "IngredientIndexBuilder.h"
#include "HashIndexBuilder.h"
#include "RecommendationEngine.h"
#include "HashRecommendationEngine.h"

#include <algorithm>
#include <cassert>
#include <iostream>

static std::vector<std::pair<int,int>> normalize(std::vector<std::pair<int,int>> v) {
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    return v;
}

static std::vector<int> sortedIds(const std::vector<Recipe>& recipes) {
    std::vector<int> ids;
    for (const auto& r : recipes) ids.push_back(r.id);
    std::sort(ids.begin(), ids.end());
    return ids;
}

static int checkQuery(const std::vector<std::string>& query, BTree& tree, HashIndex& hash,
                      const std::vector<Recipe>& recipes) {
    // exact match
    auto exactB = RecommendationEngine::searchExactMatch(query, tree);
    auto exactH = HashRecommendationEngine::searchExactMatch(query, hash);
    std::sort(exactB.begin(), exactB.end());
    std::sort(exactH.begin(), exactH.end());
    assert(exactB == exactH);

    // ranked matches (same recipes, same counts)
    auto rankB = normalize(RecommendationEngine::searchRankedMatches(query, tree));
    auto rankH = normalize(HashRecommendationEngine::searchRankedMatches(query, hash));
    assert(rankB == rankH);

    // recommended recipes (same set of recipes)
    auto recB = sortedIds(RecommendationEngine::recommendRecipes(query, tree, recipes));
    auto recH = sortedIds(HashRecommendationEngine::recommendRecipes(query, hash, recipes));
    assert(recB == recH);

    // single-ingredient search
    for (const auto& ing : query) {
        auto sB = sortedIds(RecommendationEngine::searchRecipes(ing, tree, recipes));
        auto sH = sortedIds(HashRecommendationEngine::searchRecipes(ing, hash, recipes));
        assert(sB == sH);
    }
    return 1;
}

int main() {
    // Small hand-made dataset
    std::vector<Recipe> recipes(4);
    recipes[0].id = 0; recipes[0].ingredients = {"milk", "sugar", "butter"};
    recipes[1].id = 1; recipes[1].ingredients = {"milk", "butter"};
    recipes[2].id = 2; recipes[2].ingredients = {"sugar"};
    recipes[3].id = 3; recipes[3].ingredients = {"flour", "milk"};

    BTree tree;
    HashIndex hash;
    IngredientIndexBuilder::buildIndex(recipes, tree);
    HashIndexBuilder::buildIndex(recipes, hash);

    int checked = 0;
    checked += checkQuery({"milk", "sugar"}, tree, hash, recipes);
    checked += checkQuery({"milk", "butter"}, tree, hash, recipes);
    checked += checkQuery({"unicorn"}, tree, hash, recipes);
    checked += checkQuery({"milk", "sugar", "butter", "flour"}, tree, hash, recipes);
    checked += checkQuery({}, tree, hash, recipes);

    // Larger synthetic dataset: 20,000 recipes drawn from 500 ingredients
    std::vector<Recipe> big(20000);
    unsigned long long seed = 12345;
    auto next = [&seed]() { seed = seed * 6364136223846793005ULL + 1442695040888963407ULL; return (int)(seed >> 33); };
    for (int i = 0; i < 20000; ++i) {
        big[i].id = i;
        int n = 3 + next() % 8;
        for (int j = 0; j < n; ++j) big[i].ingredients.push_back("ing" + std::to_string(next() % 500));
    }
    BTree bigTree;
    HashIndex bigHash;
    IngredientIndexBuilder::buildIndex(big, bigTree);
    HashIndexBuilder::buildIndex(big, bigHash);

    for (int q = 0; q < 50; ++q) {
        std::vector<std::string> query;
        int n = 1 + next() % 5;
        for (int j = 0; j < n; ++j) query.push_back("ing" + std::to_string(next() % 520)); // some misses
        checked += checkQuery(query, bigTree, bigHash, big);
    }

    std::cout << "test_engine_compare passed (" << checked << " queries, B-tree and hash agree)\n";
    return 0;
}