#include "catch2/catch.hpp"
#include "CppGraph.h"

using node = Node<std::int32_t>;
using AdjacencyList = Graph<std::int32_t>;

TEST_CASE("Test Depth First Search algorithm", "[dfs]") {
    AdjacencyList graph(7);
    graph[1].emplace_back(2);
    graph[1].emplace_back(3);
    graph[2].emplace_back(4);
    graph[3].emplace_back(5);
    graph[3].emplace_back(6);
    graph[5].emplace_back(6);

    std::string path;
    for(auto index :dfs(graph, 1)) {
        path += std::to_string(index);
    }
    CHECK((
        path == "124356"
        or path == "124365"
        or path == "135624"
        or path == "136524"
    ));
}

TEST_CASE("Test Breadth First Search algorithm", "[bfs]") {
    AdjacencyList graph(7);
    graph[1].emplace_back(2);
    graph[1].emplace_back(3);
    graph[2].emplace_back(4);
    graph[3].emplace_back(5);
    graph[3].emplace_back(6);
    graph[5].emplace_back(6);

    std::string path;
    for(auto index :bfs(graph, 1)) {
        path += std::to_string(index);
    }
    CHECK((
        path == "123456"
        or path == "123465"
        or path == "123546"
        or path == "123564"
        or path == "123645"
        or path == "123654"
        or path == "132456"
        or path == "132465"
        or path == "132546"
        or path == "132564"
        or path == "132645"
        or path == "132654"
    ));
}
