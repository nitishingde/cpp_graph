#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch2/catch.hpp>
#include "CppGraph.h"

SCENARIO("Test Graph of type: AdjacencyList, Weighted, Directed", "[Graph][AdjacencyList][Weighted][Directed]") {
    GIVEN("A adjacency list of weighted and directed edges") {
        using MyGraph = cpp_graph::Graph<std::string>;
        MyGraph graph(8, cpp_graph::LIST | cpp_graph::WEIGHTED | cpp_graph::DIRECTED);
        graph.addEdge(1, 2, new std::string("12"));
        graph.addEdge(1, 3, new std::string("13"));
        graph.addEdge(2, 4, new std::string("24"));
        graph.addEdge(3, 5, new std::string("35"));
        graph.addEdge(3, 6, new std::string("36"));
        graph.addEdge(5, 6, new std::string("56"));

        REQUIRE(graph.size() == 8);
        REQUIRE(graph[0].size() == 0);
        REQUIRE(graph[1].size() == 2);
        REQUIRE(graph[2].size() == 1);
        REQUIRE(graph[3].size() == 2);
        REQUIRE(graph[4].size() == 0);
        REQUIRE(graph[5].size() == 1);
        REQUIRE(graph[6].size() == 0);
        REQUIRE(graph[7].size() == 0);

        WHEN("Not adding a weighted edge to a weighted graph") {
            THEN("It will throw an exception") {
                REQUIRE_THROWS(graph.addEdge(0, 1));
            }
        }

        WHEN("Iterating over neighbouring nodes of node(1)") {
            for(auto edge: graph.iterateNeighbours(1)) {
                THEN("Every sourceNode of the edge should be 1") {// and edge value of sourceNode+destinationNode == weight of the edge") {
                    REQUIRE(edge.getSourceNode() == 1);
                }
                THEN("Every destination node of the edge should be either 2 or 3") {
                    REQUIRE((
                        edge.getDestinationNode() == 2 or
                        edge.getDestinationNode() == 3
                    ));
                }
                THEN("Every edge weight should be == sourceNode+destinationNode") {
                    REQUIRE(
                        std::to_string(edge.getSourceNode())+std::to_string(edge.getDestinationNode()) == *edge.getWeight()
                    );
                }
            }
        }

        WHEN("Iterating over every sourceNode") {
            for(std::int32_t sourceNode = 1; sourceNode < graph.size(); ++sourceNode) {
                for(auto edge1: graph[sourceNode]) {
                    for(auto edge2: graph[edge1.getDestinationNode()]) {
                        THEN("The neighbouring nodes of sourceNode should not have sourceNode as their neighbour, since this a directed graph") {
                            REQUIRE(edge2.getDestinationNode() != sourceNode);
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Test Graph of type: AdjacencyList, Weighted, Undirected", "[Graph][AdjacencyList][Weighted][Undirected]") {
    GIVEN("A adjacency list of weighted and undirected edges") {
        using MyGraph = cpp_graph::Graph<std::string>;
        MyGraph graph(8, cpp_graph::LIST | cpp_graph::WEIGHTED);
        graph.addEdge(1, 2, new std::string("12"));
        graph.addEdge(1, 3, new std::string("13"));
        graph.addEdge(2, 4, new std::string("24"));
        graph.addEdge(3, 5, new std::string("35"));
        graph.addEdge(3, 6, new std::string("36"));
        graph.addEdge(5, 6, new std::string("56"));

        REQUIRE(graph.size() == 8);
        REQUIRE(graph[0].size() == 0);
        REQUIRE(graph[1].size() == 2);
        REQUIRE(graph[2].size() == 2);
        REQUIRE(graph[3].size() == 3);
        REQUIRE(graph[4].size() == 1);
        REQUIRE(graph[5].size() == 2);
        REQUIRE(graph[6].size() == 2);
        REQUIRE(graph[7].size() == 0);

        WHEN("Not adding a weighted edge to a weighted graph") {
            THEN("It will throw an exception") {
                REQUIRE_THROWS(graph.addEdge(0, 1));
            }
        }

        WHEN("Iterating over neighbouring nodes of node(1)") {
            for(auto edge: graph.iterateNeighbours(1)) {
                THEN("Every sourceNode of the edge should be 1") {// and edge value of sourceNode+destinationNode == weight of the edge") {
                    REQUIRE(edge.getSourceNode() == 1);
                }
                THEN("Every destination node of the edge should be either 2 or 3") {
                    REQUIRE((
                        edge.getDestinationNode() == 2 or
                        edge.getDestinationNode() == 3
                    ));
                }
                THEN("Every edge weight should be == sourceNode+destinationNode") {
                    REQUIRE(
                        std::to_string(edge.getSourceNode())+std::to_string(edge.getDestinationNode()) == *edge.getWeight()
                    );
                }
            }
        }

        WHEN("Iterating over every sourceNode") {
            for(std::int32_t sourceNode = 1; sourceNode < graph.size(); ++sourceNode) {
                for(auto edge1: graph[sourceNode]) {
                    bool found = false;
                    for(auto edge2: graph[edge1.getDestinationNode()]) {
                        if(edge2.getDestinationNode() == sourceNode) {
                            found = true;
                            break;
                        }
                    }
                    THEN("The neighbouring nodes of sourceNode should have sourceNode as their neighbour, since this a directed graph") {
                        REQUIRE(found == true);
                    }
                }
            }
        }
    }
}

SCENARIO("Test Graph of type: AdjacencyList, Unweighted, Directed", "[Graph][AdjacencyList][Unweighted][Directed]") {
    GIVEN("A adjacency list of directed edges") {
        using MyGraph = cpp_graph::Graph<>;
        MyGraph graph(8, cpp_graph::LIST | cpp_graph::DIRECTED);
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 4);
        graph.addEdge(3, 5);
        graph.addEdge(3, 6);
        graph.addEdge(5, 6);

        REQUIRE(graph.size() == 8);
        REQUIRE(graph[0].size() == 0);
        REQUIRE(graph[1].size() == 2);
        REQUIRE(graph[2].size() == 1);
        REQUIRE(graph[3].size() == 2);
        REQUIRE(graph[4].size() == 0);
        REQUIRE(graph[5].size() == 1);
        REQUIRE(graph[6].size() == 0);
        REQUIRE(graph[7].size() == 0);

        WHEN("Adding weighted edge to a unweighted graph") {
            THEN("It will throw an exception") {
                REQUIRE_THROWS(graph.addEdge(0, 1, new std::int8_t()));
            }
        }

        WHEN("Iterating over neighbouring nodes of node(1)") {
            for(auto edge: graph.iterateNeighbours(1)) {
                THEN("Every sourceNode of the edge should be 1") {// and edge value of sourceNode+destinationNode == weight of the edge") {
                    REQUIRE(edge.getSourceNode() == 1);
                }
                THEN("Every destination node of the edge should be either 2 or 3") {
                    REQUIRE((
                        edge.getDestinationNode() == 2 or
                        edge.getDestinationNode() == 3
                    ));
                }
                THEN("Every edge weight should be null") {
                    REQUIRE(edge.getWeight() == nullptr);
                }
            }
        }

        WHEN("Iterating over every sourceNode") {
            for(std::int32_t sourceNode = 1; sourceNode < graph.size(); ++sourceNode) {
                for(auto edge1: graph[sourceNode]) {
                    for(auto edge2: graph[edge1.getDestinationNode()]) {
                        THEN("The neighbouring nodes of sourceNode should not have sourceNode as their neighbour, since this a directed graph") {
                            REQUIRE(edge2.getDestinationNode() != sourceNode);
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Test Graph of type: AdjacencyList, Unweighted, Undirected", "[Graph][AdjacencyList][Unweighted][Undirected]") {
    GIVEN("A adjacency list of undirected edges") {
        using MyGraph = cpp_graph::Graph<>;
        MyGraph graph(8, cpp_graph::LIST);
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 4);
        graph.addEdge(3, 5);
        graph.addEdge(3, 6);
        graph.addEdge(5, 6);

        REQUIRE(graph.size() == 8);
        REQUIRE(graph[0].size() == 0);
        REQUIRE(graph[1].size() == 2);
        REQUIRE(graph[2].size() == 2);
        REQUIRE(graph[3].size() == 3);
        REQUIRE(graph[4].size() == 1);
        REQUIRE(graph[5].size() == 2);
        REQUIRE(graph[6].size() == 2);
        REQUIRE(graph[7].size() == 0);

        WHEN("Adding weighted edge to a unweighted graph") {
            THEN("It will throw an exception") {
                REQUIRE_THROWS(graph.addEdge(0, 1, new std::int8_t()));
            }
        }

        WHEN("Iterating over neighbouring nodes of node(1)") {
            for(auto edge: graph.iterateNeighbours(1)) {
                THEN("Every sourceNode of the edge should be 1") {// and edge value of sourceNode+destinationNode == weight of the edge") {
                    REQUIRE(edge.getSourceNode() == 1);
                }
                THEN("Every destination node of the edge should be either 2 or 3") {
                    REQUIRE((
                        edge.getDestinationNode() == 2 or
                        edge.getDestinationNode() == 3
                    ));
                }
                THEN("Every edge weight should be null") {
                    REQUIRE(edge.getWeight() == nullptr);
                }
            }
        }

        WHEN("Iterating over every sourceNode") {
            for(std::int32_t sourceNode = 1; sourceNode < graph.size(); ++sourceNode) {
                for(auto edge1: graph[sourceNode]) {
                    bool found = false;
                    for(auto edge2: graph[edge1.getDestinationNode()]) {
                        if(edge2.getDestinationNode() == sourceNode) {
                            found = true;
                            break;
                        }
                    }
                    THEN("The neighbouring nodes of sourceNode should have sourceNode as their neighbour, since this a directed graph") {
                        REQUIRE(found == true);
                    }
                }
            }
        }
    }
}

SCENARIO("Test Graph of type: AdjacencyMatrix, Weighted, Directed", "[Graph][AdjacencyMatrix][Weighted][Directed]") {
    GIVEN("A adjacency matrix of weighted and directed edges") {
        using MyGraph = cpp_graph::Graph<std::string>;
        MyGraph graph(8, cpp_graph::WEIGHTED | cpp_graph::DIRECTED);
        graph.addEdge(1, 2, new std::string("12"));
        graph.addEdge(1, 3, new std::string("13"));
        graph.addEdge(2, 4, new std::string("24"));
        graph.addEdge(3, 5, new std::string("35"));
        graph.addEdge(3, 6, new std::string("36"));
        graph.addEdge(5, 6, new std::string("56"));

        REQUIRE(graph.size() == 8);
        REQUIRE(graph[0].size() == graph.size());
        REQUIRE(graph[1].size() == graph.size());
        REQUIRE(graph[2].size() == graph.size());
        REQUIRE(graph[3].size() == graph.size());
        REQUIRE(graph[4].size() == graph.size());
        REQUIRE(graph[5].size() == graph.size());
        REQUIRE(graph[6].size() == graph.size());
        REQUIRE(graph[7].size() == graph.size());

        WHEN("Not adding a weighted edge to a weighted graph") {
            THEN("It will throw an exception") {
                REQUIRE_THROWS(graph.addEdge(0, 1));
            }
        }

        WHEN("Iterating over neighbouring nodes of node(1)") {
            for(auto edge: graph.iterateNeighbours(1)) {
                THEN("Every sourceNode of the edge should be 1") {// and edge value of sourceNode+destinationNode == weight of the edge") {
                    REQUIRE(edge.getSourceNode() == 1);
                }
                THEN("Every destination node of the edge should be either 2 or 3") {
                    REQUIRE((
                        edge.getDestinationNode() == 2 or
                        edge.getDestinationNode() == 3
                    ));
                }
                THEN("Every edge weight should be == sourceNode+destinationNode") {
                    REQUIRE(
                        std::to_string(edge.getSourceNode())+std::to_string(edge.getDestinationNode()) == *edge.getWeight()
                    );
                }
            }
        }

        WHEN("Iterating over every sourceNode") {
            for(std::int32_t sourceNode = 1; sourceNode < graph.size(); ++sourceNode) {
                for(auto edge1: graph[sourceNode]) {
                    for(auto edge2: graph[edge1.getDestinationNode()]) {
                        THEN("The neighbouring nodes of sourceNode should not have sourceNode as their neighbour, since this a directed graph") {
                            REQUIRE(edge2.getDestinationNode() != sourceNode);
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Test Graph of type: AdjacencyMatrix, Weighted, Undirected", "[Graph][AdjacencyMatrix][Weighted][Undirected]") {
    GIVEN("A adjacency matrix of weighted and undirected edges") {
        using MyGraph = cpp_graph::Graph<std::string>;
        MyGraph graph(8, cpp_graph::WEIGHTED);
        graph.addEdge(1, 2, new std::string("12"));
        graph.addEdge(1, 3, new std::string("13"));
        graph.addEdge(2, 4, new std::string("24"));
        graph.addEdge(3, 5, new std::string("35"));
        graph.addEdge(3, 6, new std::string("36"));
        graph.addEdge(5, 6, new std::string("56"));

        REQUIRE(graph.size() == 8);
        REQUIRE(graph[0].size() == graph.size());
        REQUIRE(graph[1].size() == graph.size());
        REQUIRE(graph[2].size() == graph.size());
        REQUIRE(graph[3].size() == graph.size());
        REQUIRE(graph[4].size() == graph.size());
        REQUIRE(graph[5].size() == graph.size());
        REQUIRE(graph[6].size() == graph.size());
        REQUIRE(graph[7].size() == graph.size());

        WHEN("Not adding a weighted edge to a weighted graph") {
            THEN("It will throw an exception") {
                REQUIRE_THROWS(graph.addEdge(0, 1));
            }
        }

        WHEN("Iterating over neighbouring nodes of node(1)") {
            for(auto edge: graph.iterateNeighbours(1)) {
                THEN("Every sourceNode of the edge should be 1") {// and edge value of sourceNode+destinationNode == weight of the edge") {
                    REQUIRE(edge.getSourceNode() == 1);
                }
                THEN("Every destination node of the edge should be either 2 or 3") {
                    REQUIRE((
                        edge.getDestinationNode() == 2 or
                        edge.getDestinationNode() == 3
                    ));
                }
                THEN("Every edge weight should be == sourceNode+destinationNode") {
                    REQUIRE(
                        std::to_string(edge.getSourceNode())+std::to_string(edge.getDestinationNode()) == *edge.getWeight()
                    );
                }
            }
        }

        WHEN("Iterating over every sourceNode") {
            for(std::int32_t sourceNode = 1; sourceNode < graph.size(); ++sourceNode) {
                for(auto edge1: graph[sourceNode]) {
                    bool found = false;
                    for(auto edge2: graph[edge1.getDestinationNode()]) {
                        if(edge2.getDestinationNode() == sourceNode) {
                            found = true;
                            break;
                        }
                    }
                    THEN("The neighbouring nodes of sourceNode should have sourceNode as their neighbour, since this a directed graph") {
                        REQUIRE(found == true);
                    }
                }
            }
        }
    }
}

SCENARIO("Test Graph of type: AdjacencyMatrix, Unweighted, Directed", "[Graph][AdjacencyMatrix][Unweighted][Directed]") {
    GIVEN("A adjacency matrix of directed edges") {
        using MyGraph = cpp_graph::Graph<>;
        MyGraph graph(8, cpp_graph::DIRECTED);
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 4);
        graph.addEdge(3, 5);
        graph.addEdge(3, 6);
        graph.addEdge(5, 6);

        REQUIRE(graph.size() == 8);
        REQUIRE(graph[0].size() == graph.size());
        REQUIRE(graph[1].size() == graph.size());
        REQUIRE(graph[2].size() == graph.size());
        REQUIRE(graph[3].size() == graph.size());
        REQUIRE(graph[4].size() == graph.size());
        REQUIRE(graph[5].size() == graph.size());
        REQUIRE(graph[6].size() == graph.size());
        REQUIRE(graph[7].size() == graph.size());

        WHEN("Adding weighted edge to a unweighted graph") {
            THEN("It will throw an exception") {
                REQUIRE_THROWS(graph.addEdge(0, 1, new std::int8_t()));
            }
        }

        WHEN("Iterating over neighbouring nodes of node(1)") {
            for(auto edge: graph.iterateNeighbours(1)) {
                THEN("Every sourceNode of the edge should be 1") {// and edge value of sourceNode+destinationNode == weight of the edge") {
                    REQUIRE(edge.getSourceNode() == 1);
                }
                THEN("Every destination node of the edge should be either 2 or 3") {
                    REQUIRE((
                        edge.getDestinationNode() == 2 or
                        edge.getDestinationNode() == 3
                    ));
                }
                THEN("Every edge weight should be null") {
                    REQUIRE(edge.getWeight() == nullptr);
                }
            }
        }

        WHEN("Iterating over every sourceNode") {
            for(std::int32_t sourceNode = 1; sourceNode < graph.size(); ++sourceNode) {
                for(auto edge1: graph[sourceNode]) {
                    for(auto edge2: graph[edge1.getDestinationNode()]) {
                        THEN("The neighbouring nodes of sourceNode should not have sourceNode as their neighbour, since this a directed graph") {
                            REQUIRE(edge2.getDestinationNode() != sourceNode);
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Test Graph of type: AdjacencyMatrix, Unweighted, Undirected", "[Graph][AdjacencyMatrix][Unweighted][Undirected]") {
    GIVEN("A adjacency matrix of undirected edges") {
        using MyGraph = cpp_graph::Graph<>;
        MyGraph graph(8, cpp_graph::MATRIX);
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 4);
        graph.addEdge(3, 5);
        graph.addEdge(3, 6);
        graph.addEdge(5, 6);

        REQUIRE(graph.size() == 8);
        REQUIRE(graph[0].size() == graph.size());
        REQUIRE(graph[1].size() == graph.size());
        REQUIRE(graph[2].size() == graph.size());
        REQUIRE(graph[3].size() == graph.size());
        REQUIRE(graph[4].size() == graph.size());
        REQUIRE(graph[5].size() == graph.size());
        REQUIRE(graph[6].size() == graph.size());
        REQUIRE(graph[7].size() == graph.size());

        WHEN("Adding weighted edge to a unweighted graph") {
            THEN("It will throw an exception") {
                REQUIRE_THROWS(graph.addEdge(0, 1, new std::int8_t()));
            }
        }

        WHEN("Iterating over neighbouring nodes of node(1)") {
            for(auto edge: graph.iterateNeighbours(1)) {
                THEN("Every sourceNode of the edge should be 1") {// and edge value of sourceNode+destinationNode == weight of the edge") {
                    REQUIRE(edge.getSourceNode() == 1);
                }
                THEN("Every destination node of the edge should be either 2 or 3") {
                    REQUIRE((
                                edge.getDestinationNode() == 2 or
                                edge.getDestinationNode() == 3
                            ));
                }
                THEN("Every edge weight should be null") {
                    REQUIRE(edge.getWeight() == nullptr);
                }
            }
        }

        WHEN("Iterating over every sourceNode") {
            for(std::int32_t sourceNode = 1; sourceNode < graph.size(); ++sourceNode) {
                for(auto edge1: graph[sourceNode]) {
                    bool found = false;
                    for(auto edge2: graph[edge1.getDestinationNode()]) {
                        if(edge2.getDestinationNode() == sourceNode) {
                            found = true;
                            break;
                        }
                    }
                    THEN("The neighbouring nodes of sourceNode should have sourceNode as their neighbour, since this a directed graph") {
                        REQUIRE(found == true);
                    }
                }
            }
        }
    }
}
