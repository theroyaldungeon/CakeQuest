//
// Created by maldo on 11/2/2026.
//

#include "BTree.h"
#include <iostream>

int main() {
    BTree tree;

    IngredientEntry a;
    a.ingredient = "milk";

    IngredientEntry b;
    b.ingredient = "butter";

    IngredientEntry c;
    c.ingredient = "eggs";

    IngredientEntry d;
    d.ingredient = "flour";

    IngredientEntry e;
    e.ingredient = "apple";

    IngredientEntry f;
    f.ingredient = "sugar";

    IngredientEntry g;
    g.ingredient = "vanilla";

    tree.insert(a);
    tree.insert(b);
    tree.insert(c);
    tree.insert(d);
    tree.insert(e);
    tree.insert(f);
    tree.insert(g);

    IngredientEntry* result = tree.search("butter");

    if(result != nullptr) {
        std::cout << result->ingredient << std::endl;
    }

    return 0;
}