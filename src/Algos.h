#ifndef CPP_GRAPH_ALGOS_H
#define CPP_GRAPH_ALGOS_H


#include "Graph.h"
#include <vector>
#include <deque>
#include <functional>

namespace cpp_graph {
    /**
     * Depth First Search on cpp_graph::Graph
     * @tparam EdgeWeight datatype used by graph parameter
     * @param graph cpp_graph::Graph
     * @param node cpp_graph::Node
     * @return tuple(std::vector<cpp_graph::Node> timeIn, std::vector<uint32_t> timeOut)
     */
    template<typename EdgeWeight>
    auto dfs(const Graph <EdgeWeight> &graph, const Node &node) {
        std::vector<uint32_t> timeIn(graph.size(), 0);
        std::vector<uint32_t> timeOut(graph.size(), 0);
        uint32_t timer = 0;
        std::vector<DfsColour> colour(graph.size(), DfsColour::WHITE);

        // core algorithm
        std::function<void(const Graph<EdgeWeight> &, const Node &)> _dfs = nullptr;
        _dfs = [&timeIn, &timeOut, &timer, &colour, &_dfs](const Graph<EdgeWeight> &graph, const Node &node) {
            timeIn[node] = timer++;
            colour[node] = DfsColour::GRAY;
            for(auto edge: graph.iterateNeighbours(node)) {
                if(colour[edge.getDestinationNode()] == DfsColour::WHITE) {
                    _dfs(graph, edge.getDestinationNode());
                }
            }
            timeOut[node] = timer++;
            colour[node] = DfsColour::BLACK;
        };

        _dfs(graph, node);

        return std::make_tuple(timeIn, timeOut);
    }

    /**
     * Depth First Search on graph represented by std containers
     * @tparam GraphDatum
     * @param graph
     * @param node cpp_graph::Node
     * @param getDestinationNode lambda function that returns other node from a given sourceNode and adjacencyList index
     * @return tuple(std::vector<cpp_graph::Node> timeIn, std::vector<uint32_t> timeOut)
     */
    template<typename GraphDatum>
    auto dfs(
        const std::vector<std::vector<GraphDatum>> &graph,
        const Node &node,
        const std::function<Node(const Node &, const size_t &)> &getDestinationNode
    ) {
        std::vector<uint32_t> timeIn(graph.size(), 0);
        std::vector<uint32_t> timeOut(graph.size(), 0);
        uint32_t timer = 0;
        std::vector<DfsColour> colour(graph.size(), DfsColour::WHITE);

        // core algorithm
        std::function<void(const std::vector<std::vector<GraphDatum>> &, const Node &)> _dfs = nullptr;
        _dfs = [&getDestinationNode, &timeIn, &timeOut, &timer, &colour, &_dfs](const std::vector<std::vector<GraphDatum>> &graph, const Node &node) {
            timeIn[node] = timer++;
            colour[node] = DfsColour::GRAY;
            for(size_t idx = 0; idx < graph[node].size(); ++idx) {
                auto destinationNode = getDestinationNode(node, idx);
                if(colour[destinationNode] == DfsColour::WHITE) {
                    _dfs(graph, destinationNode);
                }
            }
            timeOut[node] = timer++;
            colour[node] = DfsColour::BLACK;
        };

        _dfs(graph, node);

        return std::make_tuple(timeIn, timeOut);
    }

    bool isAncestor(
        const Node &ancestor,
        const Node &descendant,
        const std::vector<uint32_t> &timeIn,
        const std::vector<uint32_t> &timeOut
    );

    bool isDescendant(
        const Node &descendant,
        const Node &ancestor,
        const std::vector<uint32_t> &timeIn,
        const std::vector<uint32_t> &timeOut
    );

    /**
     * Breadth First Search on cpp_graph::Graph
     * @tparam EdgeWeight datatype used by graph parameter
     * @param graph cpp_graph::Graph
     * @param node cpp_graph::Node
     * @return tuple(std::vector<cpp_graph::Node> parents, std::vector<uint32_t> distances)
     */
    template<typename EdgeWeight>
    auto bfs(const Graph<EdgeWeight> &graph, const Node &node) {
        std::vector<Node> parents(graph.size(), -1);
        std::vector<std::uint32_t> distances(graph.size(), UINT32_MAX);
        std::deque<Node> queue;

        //@macro
        auto processNode = [&parents, &distances, &queue](const Node &node, const Node &parentNode) {
            parents[node] = parentNode;
            // (UINT32_MAX + 1) == 0, therefore for sourceNode, the distance becomes 0
            distances[node] = distances[parentNode] + 1;
            queue.emplace_back(node);
        };
        //@macro
        auto isNodeVisited = [&parents](const Node &node) {
            return parents[node] != Node(-1);
        };

        // core algorithm
        processNode(node, node);
        for(; !queue.empty(); queue.pop_front()) {
            for(auto edge: graph.iterateNeighbours(queue.front())) {
                if(!isNodeVisited(edge.getDestinationNode())) {
                    processNode(edge.getDestinationNode(), edge.getSourceNode());
                }
            }
        }
        return std::make_tuple(parents, distances);
    }

    /**
     * Breadth First Search on graph represented by std containers
     * @tparam GraphDatum datatype used by graph parameter
     * @param graph
     * @param node cpp_graph::Node
     * @param getDestinationNode lambda function that returns other node from a given sourceNode and adjacencyList index
     * @return tuple(std::vector<cpp_graph::Node> parents, std::vector<uint32_t> distances)
     */
    template<typename GraphDatum>
    auto bfs(
        const std::vector<std::vector<GraphDatum>> &graph,
        const Node &node,
        const std::function<Node(const Node &, const size_t &)> &getDestinationNode
    ) {
        std::vector<Node> parents(graph.size(), -1);
        std::vector<std::uint32_t> distances(graph.size(), UINT32_MAX);
        std::deque<std::int32_t> queue;

        //@macro
        auto processNode = [&parents, &distances, &queue](const Node &node, const Node &parentNode) {
            parents[node] = parentNode;
            // (UINT32_MAX + 1) == 0, therefore for sourceNode, the distance becomes 0
            distances[node] = distances[parentNode] + 1;
            queue.emplace_back(node);
        };
        //@macro
        auto isNodeVisited = [&parents](const Node &node) {
            return parents[node] != Node(-1);
        };

        // core algorithm
        processNode(node, node);
        for(; !queue.empty(); queue.pop_front()) {
            auto sourceNode = queue.front();
            for(size_t idx = 0; idx < graph[sourceNode].size(); ++idx) {
                auto destinationNode = getDestinationNode(sourceNode, idx);
                if(!isNodeVisited(destinationNode)) {
                    processNode(destinationNode, sourceNode);
                }
            }
        }
        return std::make_tuple(parents, distances);
    }
}

#endif //CPP_GRAPH_ALGOS_H
