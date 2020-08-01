cmake_minimum_required(VERSION 3.16)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Catch2")

add_executable(unit_tests
    Test_graphs.cpp
    Test_algos.cpp
)

target_link_libraries(unit_tests
    PUBLIC
        cpp_graph
        Catch2::Catch2
)
