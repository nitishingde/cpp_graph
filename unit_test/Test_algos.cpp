#include "catch2/catch.hpp"
#include "CppGraph.h"

TEST_CASE("Test Depth First Search algorithm", "[dfs][List][Unweighted][Directed]") {
    cpp_graph::Graph<> graph(7, cpp_graph::LIST|cpp_graph::DIRECTED);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(3, 6);
    graph.addEdge(5, 6);

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

//TEST_CASE("Test Breadth First Search algorithm", "[bfs]") {
//    cpp_graph::Graph<> graph(7, cpp_graph::LIST|cpp_graph::DIRECTED);
//    graph.addEdge(1, 2);
//    graph.addEdge(1, 3);
//    graph.addEdge(2, 4);
//    graph.addEdge(3, 5);
//    graph.addEdge(3, 6);
//    graph.addEdge(5, 6);
//
//    std::string path;
//    for(auto index :bfs(graph, 1)) {
//        path += std::to_string(index);
//    }
//    CHECK((
//        path == "123456"
//        or path == "123465"
//        or path == "123546"
//        or path == "123564"
//        or path == "123645"
//        or path == "123654"
//        or path == "132456"
//        or path == "132465"
//        or path == "132546"
//        or path == "132564"
//        or path == "132645"
//        or path == "132654"
//    ));
//}
