<<<<<<< HEAD
#include "HashIndex.h"
#include <cassert>
#include <iostream>

int main() {
    HashIndex h;
    h.insert({"flour", {1, 2, 3}});
    h.insert({"sugar", {2, 4}});
    h.insert({"flour", {9}});
    assert(h.size() == 2);
    assert((h.queryIngredient("flour") == std::vector<int>{1, 2, 3, 9}));
    assert(h.queryIngredient("unicorn").empty());
    std::cout << "test_hash passed\n";
}
=======
//
// Created by maldo on 11/2/2026.
//
>>>>>>> temp-Connection-of-Front-end-to-backened,-still-minor-filtering-errors
