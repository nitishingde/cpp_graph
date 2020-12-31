#include "catch2/catch.hpp"
#include "CppGraph.h"
#include <iostream>

TEST_CASE("Test Depth First Search algorithm with cpp_graph::Graph", "[dfs][Graph][List][Unweighted][Directed]") {
    cpp_graph::Graph<> graph(7, cpp_graph::LIST|cpp_graph::DIRECTED);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(3, 6);
    graph.addEdge(5, 6);

    auto times = cpp_graph::dfs(graph, 1);
    std::vector<uint32_t> &timeIn = std::get<0>(times);
    std::vector<uint32_t> &timeOut = std::get<1>(times);
    CHECK(cpp_graph::isDescendant(2, 1, timeIn, timeOut));
    CHECK(cpp_graph::isDescendant(3, 1, timeIn, timeOut));
    CHECK(cpp_graph::isDescendant(4, 2, timeIn, timeOut));
    CHECK(cpp_graph::isDescendant(5, 3, timeIn, timeOut));
    CHECK(cpp_graph::isDescendant(6, 3, timeIn, timeOut));
}

TEST_CASE("Test Depth First Search algorithm with std::container", "[dfs][std][List][Unweighted][Directed]") {
    std::vector<std::vector<std::pair<std::int32_t, std::string>>> graph(8);
    graph[1].emplace_back(std::make_pair(2, "12"));
    graph[1].emplace_back(std::make_pair(3, "13"));
    graph[2].emplace_back(std::make_pair(4, "24"));
    graph[3].emplace_back(std::make_pair(5, "35"));
    graph[3].emplace_back(std::make_pair(6, "36"));
    graph[5].emplace_back(std::make_pair(6, "56"));

    auto times = cpp_graph::dfs(
        graph,
        1,
        [](const auto &graphDatum) {
            return graphDatum.first;
        }
    );

    std::vector<uint32_t> &timeIn = std::get<0>(times);
    std::vector<uint32_t> &timeOut = std::get<1>(times);
    CHECK(cpp_graph::isDescendant(2, 1, timeIn, timeOut));
    CHECK(cpp_graph::isDescendant(3, 1, timeIn, timeOut));
    CHECK(cpp_graph::isDescendant(4, 2, timeIn, timeOut));
    CHECK(cpp_graph::isDescendant(5, 3, timeIn, timeOut));
    CHECK(cpp_graph::isDescendant(6, 3, timeIn, timeOut));
}

TEST_CASE("Test Breadth First Search algorithm with cpp_graph::Graph", "[bfs][Graph][List][Unweighted][Directed]") {
    cpp_graph::Graph<> graph(8, cpp_graph::LIST|cpp_graph::DIRECTED);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(3, 6);
    graph.addEdge(5, 6);

    auto parent_distance = cpp_graph::bfs(graph, 1);

    auto &parent = std::get<0>(parent_distance);
    auto actualParent = std::vector<cpp_graph::Node>({-1, 1, 1, 1, 2, 3, 3, -1});
    CHECK(parent.size() == graph.size());
    CHECK(parent.size() == actualParent.size());
    for(size_t i = 0; i < parent.size(); i++) {
        CHECK(parent[i] == actualParent[i]);
    }

    auto &distance = std::get<1>(parent_distance);
    auto actualDistance = std::vector<std::uint32_t>({UINT32_MAX, 0, 1, 1, 2, 2, 2, UINT32_MAX});
    CHECK(distance.size() == graph.size());
    CHECK(distance.size() == actualDistance.size());
    for(size_t i = 0; i < distance.size(); i++) {
        CHECK(distance[i] == actualDistance[i]);
    }
}

TEST_CASE("Test Breadth First Search algorithm with std::container", "[bfs][std][List][Unweighted][Directed]") {
    std::vector<std::vector<std::pair<std::int32_t, std::string>>> graph(8);
    graph[1].emplace_back(std::make_pair(2, "12"));
    graph[1].emplace_back(std::make_pair(3, "13"));
    graph[2].emplace_back(std::make_pair(4, "24"));
    graph[3].emplace_back(std::make_pair(5, "35"));
    graph[3].emplace_back(std::make_pair(6, "36"));
    graph[5].emplace_back(std::make_pair(6, "56"));

    auto parent_distance = cpp_graph::bfs(
        graph,
        1,
        [](const auto &graphDatum) {
            return graphDatum.first;
        }
    );

    auto &parent = std::get<0>(parent_distance);
    auto actualParent = std::vector<cpp_graph::Node>({-1, 1, 1, 1, 2, 3, 3, -1});
    CHECK(parent.size() == graph.size());
    CHECK(parent.size() == actualParent.size());
    for(size_t i = 0; i < parent.size(); i++) {
        CHECK(parent[i] == actualParent[i]);
    }

    auto &distance = std::get<1>(parent_distance);
    auto actualDistance = std::vector<std::uint32_t>({UINT32_MAX, 0, 1, 1, 2, 2, 2, UINT32_MAX});
    CHECK(distance.size() == graph.size());
    CHECK(distance.size() == actualDistance.size());
    for(size_t i = 0; i < distance.size(); i++) {
        CHECK(distance[i] == actualDistance[i]);
    }
}
