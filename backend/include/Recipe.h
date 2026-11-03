//
// Created by maldo on 11/2/2026.
//

#ifndef CAKEQUEST_RECIPE_H
#define CAKEQUEST_RECIPE_H

#include <string>
#include <vector>

struct Recipe {
    int id;
    std::string title;
    std::vector<std::string> ingredients;
    std::vector<std::string> directions;
    std::string link;
    std::string source;
    std::string site;
};

#endif