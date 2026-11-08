cmake_minimum_required(VERSION 3.20)

project(CakeQuest)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    backend/include
    external
)

add_executable(
        CakeQuest

        backend/src/main.cpp

        backend/src/BTree.cpp
        backend/src/RecipeLoader.cpp
        backend/src/HashIndex.cpp
        backend/src/MinHeap.cpp
        backend/src/RecommendationEngine.cpp
        backend/src/IngredientIndexBuilder.cpp
)

set_target_properties(CakeQuest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_executable(
        test_btree

        backend/src/BTree.cpp
        backend/tests/test_btree.cpp
)

add_executable(
        test_loader

        backend/src/RecipeLoader.cpp
        backend/tests/test_loader.cpp
)

add_executable(
        test_hash

        backend/src/HashIndex.cpp
        backend/tests/test_hash.cpp
)

add_executable(
        test_heap

        backend/src/MinHeap.cpp
        backend/tests/test_heap.cpp
)

add_executable(
        test_index_builder

        backend/src/BTree.cpp
        backend/src/RecipeLoader.cpp
        backend/src/IngredientIndexBuilder.cpp
        backend/tests/test_index_builder.cpp
)

add_executable(
        test_recommendation_engine

        backend/src/BTree.cpp
        backend/src/RecipeLoader.cpp
        backend/src/IngredientIndexBuilder.cpp
        backend/src/RecommendationEngine.cpp

        backend/tests/test_recommendation_engine.cpp
)