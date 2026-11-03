cmake_minimum_required(VERSION 3.20)

project(CakeQuest)

set(CMAKE_CXX_STANDARD 17)

include_directories(backend/include)

add_executable(
        CakeQuest
        backend/src/BTree.cpp
        backend/tests/test_btree.cpp
)