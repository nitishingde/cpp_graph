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

    SECTION("Graph based") {
        std::string path;
        for(auto index :cpp_graph::dfs(graph, 1)) {
            path += std::to_string(index);
        }
        CHECK((
            path == "124356"
            or path == "124365"
            or path == "135624"
            or path == "136524"
        ));
    }

    SECTION("STDGraph based") {
        std::string path;
        auto traversalPath = cpp_graph::dfs<decltype(graph), cpp_graph::Edge<>>(
            graph,
            1,
            [](const cpp_graph::Edge<> &edge) {
                return edge.getDestinationNode();
            }
        );
        for(auto index :traversalPath) {
            path += std::to_string(index);
        }
        CHECK((
            path == "124356"
            or path == "124365"
            or path == "135624"
            or path == "136524"
        ));
    }
}

TEST_CASE("Test Depth First Search algorithm with std::container", "[dfs][std][List][Unweighted][Directed]") {
    std::vector<std::vector<std::pair<std::int32_t, std::string>>> graph(8);
    graph[1].emplace_back(std::make_pair(2, "12"));
    graph[1].emplace_back(std::make_pair(3, "13"));
    graph[2].emplace_back(std::make_pair(4, "24"));
    graph[3].emplace_back(std::make_pair(5, "35"));
    graph[3].emplace_back(std::make_pair(6, "36"));
    graph[5].emplace_back(std::make_pair(6, "56"));

    std::string path;
    auto traversalPath = cpp_graph::dfs<decltype(graph), std::pair<std::int32_t, std::string>>(
        graph,
        1,
        [](const std::pair<std::int32_t, std::string> &edge) {
            return edge.first;
        }
    );
    for(auto index: traversalPath) {
        path += std::to_string(index);
    }
    CHECK((
        path == "124356"
        or path == "124365"
        or path == "135624"
        or path == "136524"
    ));
}

TEST_CASE("Test Breadth First Search algorithm with cpp_graph::Graph", "[bfs][Graph][List][Unweighted][Directed]") {
    cpp_graph::Graph<> graph(8, cpp_graph::LIST|cpp_graph::DIRECTED);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(3, 6);
    graph.addEdge(5, 6);

    SECTION("Graph based") {
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
        [&graph](const cpp_graph::Node &sourceNode, const size_t &index) {
            return graph[sourceNode][index].first;
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
