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

    std::string path;
    for(auto index :dfs(graph, 1)) {
        path += std::to_string(index);
    }
    CHECK((
        path == "124356"
        or path == "123465"
        or path == "135624"
        or path == "136524"
    ));
}
