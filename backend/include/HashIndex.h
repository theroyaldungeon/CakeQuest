//
// Created by maldo on 11/2/2026.
//

#ifndef CAKEQUEST_HASHINDEX_H
#define CAKEQUEST_HASHINDEX_H

#include "IngredientEntry.h"

#include <cstddef>
#include <string>
#include <vector>

class HashIndex {
private:
    struct Node {
        IngredientEntry entry;
        Node* next;
    };

    std::vector<Node*> buckets;
    std::size_t numEntries;

    std::size_t hashString(const std::string& key) const;
    std::size_t bucketIndex(const std::string& key, std::size_t bucketCount) const;
    void rehash(std::size_t newBucketCount);
    void clear();

public:
    HashIndex(std::size_t initialBuckets = 1024);
    ~HashIndex();

    //Copying is disabled so two tables never share and double-delete nodes.
    HashIndex(const HashIndex&) = delete;
    HashIndex& operator=(const HashIndex&) = delete;

    //Adds the entry.
    void insert(const IngredientEntry& entry);

    //Adds one recipe ID under an ingredient (creates the entry if needed).
    void add(const std::string& ingredient, int recipeId);

    //Returns pointer to the entry, or nullptr
    IngredientEntry* search(const std::string& ingredient);

    //Returns the recipe IDs for an ingredient
    std::vector<int> queryIngredient(const std::string& ingredient);

    // Stats for the performance comparison.
    std::size_t size() const;             //number of distinct ingredients
    std::size_t bucketCount() const;
    double loadFactor() const;
    std::size_t longestChain() const;     //worst-case collision chain length
    std::size_t memoryUsageBytes() const; //estimate
};

#endif