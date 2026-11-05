//
// Created by maldo on 11/2/2026.
//

#ifndef CAKEQUEST_RECOMMENDATIONENGINE_H
#define CAKEQUEST_RECOMMENDATIONENGINE_H

#include "BTree.h"

#include <string>
#include <vector>

class RecommendationEngine
{
public:

    static std::vector<int>
    searchByIngredient(
        const std::string& ingredient,
        BTree& tree
    );
};

#endif