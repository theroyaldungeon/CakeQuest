//edited by St Lot

#ifndef CAKEQUEST_MINHEAP_H
#define CAKEQUEST_MINHEAP_H

#include "Recipe.h"
#include <vector>

struct HeapNode {
    //traces back the recipe from JSON
    int recipeID;
    //prep time is based on the directions and only is an estimate
    //it adds times from steps like 5 mins, 1 hour
    //it doesnt account for times where steps overlap due to multitasking
    int prepTime;
};

class MinHeap {
private:
    //storing recipes that the search function returns 
    std::vector<HeapNode> prepTimes;
    void heapify(int parent);

public:
    void insert(int recipeID, int prepTime);
    HeapNode extractMin();
    bool isEmpty() const;
    int size() const;

    //how it returns the filtered results
    std::vector<int> heapSort();

};

//reads the times like 5 min out the directions
int extractTime(const std::string& direction);
int calculateTime(const Recipe& recipe);

#endif //CAKEQUEST_MINHEAP_H