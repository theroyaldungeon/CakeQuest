#include "HashIndex.h"

#include <cstdint>

// Table doubles in size when entries / buckets would exceed this value.
const double MAX_LOAD_FACTOR = 0.75;

HashIndex::HashIndex(std::size_t initialBuckets)
    : buckets(initialBuckets == 0 ? 1 : initialBuckets, nullptr), numEntries(0) {}

HashIndex::~HashIndex() {
    clear();
}

void HashIndex::clear() {
    for (Node*& head : buckets) {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }
    numEntries = 0;
}

//djb2 string hash
std::size_t HashIndex::hashString(const std::string& key) const {
    std::uint64_t hash = 5381;
    for (unsigned char c : key) {
        hash = ((hash << 5) + hash) + c; //hash * 33 + c
    }
    return static_cast<std::size_t>(hash);
}

std::size_t HashIndex::bucketIndex(const std::string& key, std::size_t bucketCount) const {
    return hashString(key) % bucketCount;
}

//Doubles the table and relinks existing nodes (no node reallocation).
void HashIndex::rehash(std::size_t newBucketCount) {
    std::vector<Node*> newBuckets(newBucketCount, nullptr);

    for (Node* head : buckets) {
        while (head != nullptr) {
            Node* next = head->next;
            std::size_t idx = bucketIndex(head->entry.ingredient, newBucketCount);
            head->next = newBuckets[idx];
            newBuckets[idx] = head;
            head = next;
        }
    }

    buckets.swap(newBuckets);
}

void HashIndex::insert(const IngredientEntry& entry) {
    //Merge into existing entry if the ingredient is already indexed
    IngredientEntry* existing = search(entry.ingredient);
    if (existing != nullptr) {
        existing->recipeIDs.insert(existing->recipeIDs.end(),
                                   entry.recipeIDs.begin(),
                                   entry.recipeIDs.end());
        return;
    }

    if (static_cast<double>(numEntries + 1) / static_cast<double>(buckets.size()) > MAX_LOAD_FACTOR) {
        rehash(buckets.size() * 2);
    }

    std::size_t idx = bucketIndex(entry.ingredient, buckets.size());
    Node* node = new Node{entry, nullptr};
    node->next = buckets[idx];
    buckets[idx] = node;
    ++numEntries;
}

void HashIndex::add(const std::string& ingredient, int recipeId) {
    IngredientEntry* existing = search(ingredient);
    if (existing != nullptr) {
        existing->recipeIDs.push_back(recipeId);
        return;
    }

    if (static_cast<double>(numEntries + 1) / static_cast<double>(buckets.size()) > MAX_LOAD_FACTOR) {
        rehash(buckets.size() * 2);
    }

    IngredientEntry entry;
    entry.ingredient = ingredient;
    entry.recipeIDs.push_back(recipeId);

    std::size_t idx = bucketIndex(ingredient, buckets.size());
    Node* node = new Node{entry, nullptr};
    node->next = buckets[idx];
    buckets[idx] = node;
    ++numEntries;
}

IngredientEntry* HashIndex::search(const std::string& ingredient) {
    std::size_t idx = bucketIndex(ingredient, buckets.size());
    for (Node* cur = buckets[idx]; cur != nullptr; cur = cur->next) {
        if (cur->entry.ingredient == ingredient) {
            return &cur->entry;
        }
    }
    return nullptr;
}

std::vector<int> HashIndex::queryIngredient(const std::string& ingredient) {
    IngredientEntry* found = search(ingredient);
    if (found == nullptr) {
        return {};
    }
    return found->recipeIDs;
}

std::size_t HashIndex::size() const {
    return numEntries;
}

std::size_t HashIndex::bucketCount() const {
    return buckets.size();
}

double HashIndex::loadFactor() const {
    return static_cast<double>(numEntries) / static_cast<double>(buckets.size());
}

std::size_t HashIndex::longestChain() const {
    std::size_t longest = 0;
    for (Node* head : buckets) {
        std::size_t len = 0;
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            ++len;
        }
        if (len > longest) longest = len;
    }
    return longest;
}

//Estimate: bucket array + nodes + ingredient strings + recipe ID vectors.
std::size_t HashIndex::memoryUsageBytes() const {
    std::size_t bytes = sizeof(HashIndex);
    bytes += buckets.capacity() * sizeof(Node*);

    for (Node* head : buckets) {
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            bytes += sizeof(Node);
            if (cur->entry.ingredient.capacity() >= 16) {
                bytes += cur->entry.ingredient.capacity() + 1;
            }
            bytes += cur->entry.recipeIDs.capacity() * sizeof(int);
        }
    }
    return bytes;
}