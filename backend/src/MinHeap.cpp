//Edited by St Lot

#include "MinHeap.h"
#include <iostream>
#include <regex>
#include <cctype>


bool MinHeap::isEmpty() const {
    return prepTimes.empty();
}

int MinHeap::size() const {
    return static_cast<int>(prepTimes.size());
}

void MinHeap::insert(int recipeID, int prepTime){

    //making a recipe node
    HeapNode newRecipe;
    newRecipe.recipeID = recipeID;
    newRecipe.prepTime = prepTime;

    prepTimes.push_back(newRecipe);

    //where its currently in the heap
    int child = size() - 1;

    while (child > 0){
        //using the heap array index strategy
        int parent = (child -1) /2;

        if (prepTimes[child].prepTime < prepTimes[parent].prepTime){
            HeapNode temp = prepTimes[parent];
            prepTimes[parent] = prepTimes[child];
            prepTimes[child] = temp;

            child = parent;
        }

        else{break;}
    }
}

void MinHeap::heapify(int parent){
    int smallest = parent;

    int left = (2*parent) +1; 
    int right = (2*parent) +2;

    if (left < size() && prepTimes[left].prepTime < prepTimes[smallest].prepTime) {
        smallest = left;
    }

    if (right < size() && prepTimes[right].prepTime < prepTimes[smallest].prepTime) {
        smallest = right;
    }

    if (smallest != parent){
        HeapNode temp = prepTimes[parent];
        prepTimes[parent] = prepTimes[smallest];
        prepTimes[smallest] = temp;

        heapify(smallest);
        
    }
}

HeapNode MinHeap::extractMin() {

    HeapNode min = prepTimes[0];

    if (size() == 1){
        prepTimes.pop_back();
        return min;
    }

    prepTimes[0] = prepTimes.back();
    prepTimes.pop_back();

    heapify(0);

    return min;
}


std::vector<int> MinHeap::heapSort(){
    std::vector<int> sortedRecipes;

    while (!isEmpty()){
        HeapNode min = extractMin();
        sortedRecipes.push_back(min.recipeID);
    }

    return sortedRecipes;
}

int extractTime(const std::string& direction){
    //conversion of seconds because some recipes mention seconds in
    int totalSecs = 0;

    std::regex timePhrases(R"((\d+)\s*(hours?|hrs?|h|minutes?|mins?|m|seconds?|secs?|s)\b)", std::regex_constants::icase);

    auto begin = std::sregex_iterator(direction.begin(), direction.end(), timePhrases);

    auto end = std::sregex_iterator();

    
    for (auto it = begin; it != end; ++it){
        int amount = std::stoi((*it)[1]);
        std::string unit = (*it)[2];
        
        //to make sure all letters are lower case; ex: Hour to hour
        for (char& c : unit){
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }


        //conversions
        if (unit == "hour" || unit == "hours" || unit == "hr" ||unit == "hrs" || unit == "h"){
            totalSecs += (amount*3600);
        }

        else if (unit == "minute" || unit == "minutes" || unit == "min" || unit == "mins" || unit == "m"){
            totalSecs += (amount*60);
        }

        else{
            totalSecs += amount;
        }
    }

    return ((totalSecs + 59)/60);
}

int calculateTime(const Recipe& recipe){
    //total time
    int total = 0;

    //looks through all the steps since directions are broken up into an array
    for (const std::string& direction : recipe.directions){
        total += extractTime(direction);
    }

    return total;
}

