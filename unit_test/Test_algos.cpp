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
    cpp_graph::Graph<> graph(7, cpp_graph::LIST|cpp_graph::DIRECTED);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(3, 6);
    graph.addEdge(5, 6);

    SECTION("Graph based") {
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

    SECTION("STDGraph based") {
        std::string path;
        auto traversalPath = cpp_graph::bfs<decltype(graph), cpp_graph::Edge<>>(
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
}

TEST_CASE("Test Breadth First Search algorithm with std::container", "[bfs][std][List][Unweighted][Directed]") {
    std::vector<std::vector<std::pair<std::int32_t, std::string>>> graph(8);
    graph[1].emplace_back(std::make_pair(2, "12"));
    graph[1].emplace_back(std::make_pair(3, "13"));
    graph[2].emplace_back(std::make_pair(4, "24"));
    graph[3].emplace_back(std::make_pair(5, "35"));
    graph[3].emplace_back(std::make_pair(6, "36"));
    graph[5].emplace_back(std::make_pair(6, "56"));

    std::string path;
    auto pathTraversed = cpp_graph::bfs<decltype(graph), std::pair<std::int32_t, std::string>>(
        graph,
        1,
        [](const std::pair<std::int32_t, std::string> &edge) {
            return edge.first;
        }
    );
    for(auto index: pathTraversed) {
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
