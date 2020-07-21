cmake_minimum_required(VERSION 3.16)
project(cpp_graph CXX)

add_library(cpp_graph
    SHARED
        src/Graph.cpp src/Graph.h
)

add_subdirectory("${CMAKE_SOURCE_DIR}/unit_test")
