
#include "MinHeap.h"
#include <iostream>
#include <vector>

int main() {

    std::cout << "===== TESTING extractTime() =====\n";

    std::cout << "30 minutes: "
              << extractTime("Bake for 30 minutes.") << "\n";

    std::cout << "1 hour: "
              << extractTime("Cook for 1 hour.") << "\n";

    std::cout << "90 seconds: "
              << extractTime("Mix for 90 seconds.") << "\n";

    std::cout << "No time: "
              << extractTime("Mix ingredients until smooth.") << "\n";


    std::cout << "\n===== TESTING calculateTime() =====\n";

    Recipe cake;

    cake.id = 1;
    cake.title = "Chocolate Cake";

    cake.directions = {
        "Mix ingredients for 5 minutes.",
        "Bake for 30 minutes.",
        "Allow cake to cool."
    };

    std::cout << cake.title << " total time: "
              << calculateTime(cake) << " minutes\n";


    std::cout << "\n===== TESTING MIN HEAP =====\n";

    MinHeap heap;

    heap.insert(12, 45);
    heap.insert(5, 15);
    heap.insert(8, 30);
    heap.insert(3, 10);
    heap.insert(21, 60);

    std::cout << "Heap size: " << heap.size() << "\n";

    std::vector<int> sortedRecipes = heap.heapSort();

    std::cout << "Sorted recipe IDs:\n";

    for (int id : sortedRecipes) {
        std::cout << id << "\n";
    }

    std::cout << "Heap empty: " << heap.isEmpty() << "\n";

    return 0;
}
