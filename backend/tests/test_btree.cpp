//
// Created by maldo on 11/2/2026.
//

#include "BTree.h"
#include <iostream>

int main() {
    BTree tree;

    IngredientEntry a;
    a.ingredient = "apple";

    IngredientEntry b;
    b.ingredient = "butter";

    IngredientEntry c;
    c.ingredient = "cinnamon";

    IngredientEntry d;
    d.ingredient = "eggs";

    IngredientEntry e;
    e.ingredient = "flour";

    IngredientEntry f;
    f.ingredient = "milk";

    IngredientEntry g;
    g.ingredient = "nutmeg";

    IngredientEntry h;
    h.ingredient = "sugar";

    IngredientEntry i;
    i.ingredient = "vanilla";

    IngredientEntry j;
    j.ingredient = "yeast";

    tree.insert(a);
    tree.insert(b);
    tree.insert(c);
    tree.insert(d);
    tree.insert(e);
    tree.insert(f);
    tree.insert(g);
    tree.insert(h);
    tree.insert(i);
    tree.insert(j);

    IngredientEntry* result1 = tree.search("milk");
    IngredientEntry* result2 = tree.search("vanilla");
    IngredientEntry* result3 = tree.search("yeast");
    IngredientEntry* result4 = tree.search("watermelon");

        std::cout << "milk: " << (result1 != nullptr) << std::endl;
        std::cout << "vanilla: " << (result2 != nullptr) << std::endl;
        std::cout << "yeast: " << (result3 != nullptr) << std::endl;
        std::cout << "watermelon: " << (result4 != nullptr) << std::endl;

    return 0;
}