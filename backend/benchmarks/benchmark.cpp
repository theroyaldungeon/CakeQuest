
#include "BTree.h"
#include "HashIndex.h"
#include "IngredientIndexBuilder.h"
#include "HashIndexBuilder.h"
#include "Recipe.h"
#include "json.hpp"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <random>
#include <string>
#include <vector>

#ifndef PROJECT_ROOT
#define PROJECT_ROOT "."
#endif


static std::size_t g_liveBytes = 0;
static const std::size_t HEADER = 16;   // keeps returned pointers 16-byte aligned

void* operator new(std::size_t size) {
    void* raw = std::malloc(size + HEADER);
    if (raw == nullptr) throw std::bad_alloc();
    *static_cast<std::size_t*>(raw) = size;
    g_liveBytes += size;
    return static_cast<char*>(raw) + HEADER;
}

void operator delete(void* p) noexcept {
    if (p == nullptr) return;
    char* raw = static_cast<char*>(p) - HEADER;
    g_liveBytes -= *reinterpret_cast<std::size_t*>(raw);
    std::free(raw);
}

void operator delete(void* p, std::size_t) noexcept { operator delete(p); }
void* operator new[](std::size_t size) { return operator new(size); }
void operator delete[](void* p) noexcept { operator delete(p); }
void operator delete[](void* p, std::size_t) noexcept { operator delete(p); }

//end of helpers

using Clock = std::chrono::steady_clock;

static double msSince(Clock::time_point start) {
    return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

static double median(std::vector<double> v) {
    std::sort(v.begin(), v.end());
    return v[v.size() / 2];
}

// Keeps the compiler from optimizing the lookup loops away.
static volatile std::size_t g_sink = 0;

struct Row {
    std::string category;
    std::string structure;
    std::size_t dataSize;
    double value;
    std::string unit;
};

static std::vector<Row> g_rows;

static void addRow(const std::string& category, const std::string& structure,
                   std::size_t dataSize, double value, const std::string& unit) {
    g_rows.push_back({category, structure, dataSize, value, unit});
}

// Median time in nanoseconds for ONE search() call.
template <typename Index>
static double timeLookups(Index& index, const std::vector<std::string>& queries,
                          int loops, int reps) {
    std::size_t warm = 0;                       // one untimed warm-up pass
    for (const auto& q : queries) {
        IngredientEntry* e = index.search(q);
        warm += e ? e->recipeIDs.size() : 1;
    }
    g_sink = g_sink + warm;

    std::vector<double> samples;
    for (int r = 0; r < reps; ++r) {
        std::size_t acc = 0;
        Clock::time_point start = Clock::now();
        for (int l = 0; l < loops; ++l) {
            for (const auto& q : queries) {
                IngredientEntry* e = index.search(q);
                acc += e ? e->recipeIDs.size() : 1;
            }
        }
        double ns = std::chrono::duration<double, std::nano>(Clock::now() - start).count();
        g_sink = g_sink + acc;
        samples.push_back(ns / (static_cast<double>(loops) * static_cast<double>(queries.size())));
    }
    return median(samples);
}

int main(int argc, char** argv) {
    const std::string dataFile = (argc > 1) ? argv[1]
        : std::string(PROJECT_ROOT) + "/data/cleaned/ner_200k.json";
    const std::string outPrefix = (argc > 2) ? argv[2]
        : std::string(PROJECT_ROOT) + "/results/benchmark_results";

    std::vector<std::vector<std::string>> allIngredients;
    {
        std::ifstream in(dataFile);
        if (!in.is_open()) {
            std::cerr << "Could not open " << dataFile << "\n"
                      << "Run: python scripts/make_benchmark_data.py\n";
            return 1;
        }
        nlohmann::json j;
        in >> j;
        allIngredients = j.get<std::vector<std::vector<std::string>>>();
    }
    const std::size_t total = allIngredients.size();
    std::cout << "Loaded " << total << " recipes from " << dataFile << "\n";
    if (total == 0) return 1;

    //different data sizes to test lookup time
    std::vector<std::size_t> sizes;
    for (std::size_t s : {10000u, 50000u, 100000u, 200000u}) {
        if (s <= total) sizes.push_back(s);
    }
    if (sizes.empty() || sizes.back() != total) sizes.push_back(total);

    const int BUILD_REPS = 5;
    const int LOOKUP_REPS = 7;
    const int LOOKUP_LOOPS = 50;
    const std::size_t QUERY_COUNT = 2000;

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "\n recipes |  build ms (btree/hash) |  hit ns (btree/hash) |  miss ns (btree/hash) |  memory MB (btree/hash)\n";

    for (std::size_t n : sizes) {
        std::vector<Recipe> recipes(n);
        for (std::size_t i = 0; i < n; ++i) {
            recipes[i].id = static_cast<int>(i);
            recipes[i].ingredients = allIngredients[i];
        }

        //memory and building
        std::size_t before = g_liveBytes;
        BTree* tree = new BTree();                 // BTree has no destructor so made one here
        IngredientIndexBuilder::buildIndex(recipes, *tree);
        const std::size_t treeBytes = g_liveBytes - before;

        before = g_liveBytes;
        HashIndex* hash = new HashIndex();
        HashIndexBuilder::buildIndex(recipes, *hash);
        const std::size_t hashBytes = g_liveBytes - before;

        addRow("memory_bytes", "btree", n, static_cast<double>(treeBytes), "bytes");
        addRow("memory_bytes", "hash",  n, static_cast<double>(hashBytes), "bytes");

        //build time (median of several builds)
        std::vector<double> treeBuild, hashBuild;
        for (int r = 0; r < BUILD_REPS; ++r) {
            BTree* t = new BTree();
            Clock::time_point start = Clock::now();
            IngredientIndexBuilder::buildIndex(recipes, *t);
            treeBuild.push_back(msSince(start));

            HashIndex* h = new HashIndex();
            start = Clock::now();
            HashIndexBuilder::buildIndex(recipes, *h);
            hashBuild.push_back(msSince(start));
            delete h;
        }
        const double treeBuildMs = median(treeBuild);
        const double hashBuildMs = median(hashBuild);
        addRow("build_ms", "btree", n, treeBuildMs, "ms");
        addRow("build_ms", "hash",  n, hashBuildMs, "ms");

        //lookup queries (fixed seed, so every run uses the same ones)
        // Hits: pick a random recipe, then a random ingredient from it, so common ingredients show up as often as they do in real searches.
        std::mt19937 rng(12345);
        std::vector<std::string> hits, misses;
        while (hits.size() < QUERY_COUNT) {
            const auto& ing = recipes[rng() % n].ingredients;
            if (ing.empty()) continue;
            hits.push_back(ing[rng() % ing.size()]);
        }
        // Misses
        for (std::size_t i = 0; i < hits.size(); ++i) {
            std::string miss = hits[i] + "_x";
            if (tree->search(miss) != nullptr) miss = "zzz_missing_" + std::to_string(i);
            misses.push_back(miss);
        }

        // agreement: both indexes must return identical recipe ID lists
        std::size_t mismatches = 0;
        for (const auto& q : hits)   if (tree->queryIngredient(q) != hash->queryIngredient(q)) ++mismatches;
        for (const auto& q : misses) if (tree->queryIngredient(q) != hash->queryIngredient(q)) ++mismatches;
        addRow("agreement_queries_checked", "both", n, static_cast<double>(hits.size() + misses.size()), "count");
        addRow("agreement_mismatches",      "both", n, static_cast<double>(mismatches), "count");
        if (mismatches != 0) std::cerr << "WARNING: " << mismatches << " mismatches at size " << n << "\n";

        //lookup time
        const double treeHit  = timeLookups(*tree, hits,   LOOKUP_LOOPS, LOOKUP_REPS);
        const double hashHit  = timeLookups(*hash, hits,   LOOKUP_LOOPS, LOOKUP_REPS);
        const double treeMiss = timeLookups(*tree, misses, LOOKUP_LOOPS, LOOKUP_REPS);
        const double hashMiss = timeLookups(*hash, misses, LOOKUP_LOOPS, LOOKUP_REPS);
        addRow("lookup_hit_ns",  "btree", n, treeHit,  "ns");
        addRow("lookup_hit_ns",  "hash",  n, hashHit,  "ns");
        addRow("lookup_miss_ns", "btree", n, treeMiss, "ns");
        addRow("lookup_miss_ns", "hash",  n, hashMiss, "ns");

        std::cout << std::setw(8) << n << " | "
                  << std::setw(9) << treeBuildMs << " / " << std::setw(7) << hashBuildMs << " | "
                  << std::setw(8) << treeHit << " / " << std::setw(6) << hashHit << " | "
                  << std::setw(9) << treeMiss << " / " << std::setw(6) << hashMiss << " | "
                  << std::setw(8) << treeBytes / 1e6 << " / " << std::setw(6) << hashBytes / 1e6 << "\n";

        delete hash;
    }

    //write results
    const std::filesystem::path outFolder = std::filesystem::path(outPrefix).parent_path();
    if (!outFolder.empty()) {
        std::filesystem::create_directories(outFolder);
    }

    {
        std::ofstream csv(outPrefix + ".csv");
        csv << "category,structure,data_size,value,unit\n";
        for (const auto& r : g_rows)
            csv << r.category << "," << r.structure << "," << r.dataSize << ","
                << std::setprecision(12) << r.value << "," << r.unit << "\n";
    }
    {
        std::ofstream js(outPrefix + ".json");
        js << "[\n";
        for (std::size_t i = 0; i < g_rows.size(); ++i) {
            const Row& r = g_rows[i];
            js << "  {\"category\":\"" << r.category << "\",\"structure\":\"" << r.structure
               << "\",\"data_size\":" << r.dataSize << ",\"value\":" << std::setprecision(12) << r.value
               << ",\"unit\":\"" << r.unit << "\"}" << (i + 1 < g_rows.size() ? "," : "") << "\n";
        }
        js << "]\n";
    }

    std::cout << "\nWrote " << outPrefix << ".csv and .json (" << g_rows.size() << " rows)\n";
    return 0;
}