#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch2/catch.hpp>
#include "CppGraph.h"

class Edge {
public:
    std::string value;
    Edge(std::string str = ""): value(str) {}
    bool operator<(const Edge &other) {
        return this->value < other.value;
    }
};

TEST_CASE("Test all graph initializations", "[Graph]") {
    Graph<std::int32_t> graph1(100);
    CHECK(graph1.getDataStore().size() == 100);

    Graph<std::int32_t> graph2 = std::vector<std::vector<Node<std::int32_t>>>(200);
    CHECK(graph2.getDataStore().size() == 200);

    Graph<Edge> graph3(300);
    CHECK(graph3.getDataStore().size() == 300);

    std::vector<std::vector<Node<Edge>>> myGraph(399);
    Graph<Edge> graph4 = std::move(myGraph);
    graph4.getDataStore().emplace_back(std::vector<Node<Edge>>());
    CHECK(graph4.getDataStore().size() == 400);

    Graph<Edge> graph5 = std::move(graph4);
    CHECK(graph5.getDataStore().size() == 400);

    Graph<Edge> realGraph(3);
    auto edge1 = new Edge("edge-01");
    realGraph[0].emplace_back(Node<Edge>(1, edge1));
    realGraph[1].emplace_back(Node<Edge>(0, edge1));
    auto edge2 = new Edge("edge-02");
    realGraph[0].emplace_back(Node<Edge>(2, edge2));
    realGraph[2].emplace_back(Node<Edge>(0, edge2));
    auto edge3 = new Edge("edge-12");
    realGraph[1].emplace_back(Node<Edge>(2, edge3));
    realGraph[2].emplace_back(Node<Edge>(1, edge3));
    CHECK(realGraph[2].back().getIndex() == 1);
    std::string result = "";
    for(auto &node: realGraph.getNeighbours(0)) {
        result += node.mpEdge->value;
    }
    CHECK(result == "edge-01edge-02");
}