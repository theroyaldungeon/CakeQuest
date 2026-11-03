cmake_minimum_required(VERSION 3.20)

project(CakeQuest)

set(CMAKE_CXX_STANDARD 17)

include_directories(backend/include)

add_executable(
        CakeQuest
        backend/src/BTree.cpp
        backend/tests/test_btree.cpp
        backend/include/Recipe.h
        backend/include/RecipeLoader.h
        backend/include/HashIndex.h
        backend/include/MinHeap.h
        backend/include/RecommendationEngine.h
        backend/src/RecipeLoader.cpp
        backend/src/HashIndex.cpp
        backend/src/MinHeap.cpp
        backend/src/RecommendationEngine.cpp
        backend/tests/test_hash.cpp
        backend/tests/test_heap.cpp
)