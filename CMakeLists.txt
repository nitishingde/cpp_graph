cmake_minimum_required(VERSION 3.16)
project(cpp_graph CXX)

add_library(cpp_graph
    SHARED
        src/Graph.h src/Graph.cpp
        src/Algos.h src/Algos.cpp
        src/CppGraph.h
)

target_include_directories(cpp_graph
    PUBLIC
        "${CMAKE_SOURCE_DIR}/src"
)

add_subdirectory("${CMAKE_SOURCE_DIR}/unit_test")

add_subdirectory("${CMAKE_SOURCE_DIR}/experiment")
