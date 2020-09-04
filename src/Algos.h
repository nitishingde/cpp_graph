#ifndef CPP_GRAPH_ALGOS_H
#define CPP_GRAPH_ALGOS_H


#include "Graph.h"
#include <vector>
#include <deque>
#include <functional>

namespace cpp_graph {
    template<typename EdgeWeight>
    std::vector<std::int32_t> dfs(const Graph <EdgeWeight> &graph, const std::int32_t &node) {
        std::vector<std::int32_t> traversalPath;
        traversalPath.reserve(graph.size());
        std::vector<bool> isVisited(graph.size());

        // core algorithm
        std::function<void(const Graph<EdgeWeight> &, const std::int32_t &)> _dfs = nullptr;
        _dfs = [&traversalPath, &isVisited, &_dfs](const Graph<EdgeWeight> &graph, const std::int32_t &node) {
            if(isVisited[node]) return;

            isVisited[node] = true;
            traversalPath.emplace_back(node);
            for(auto edge: graph.iterateNeighbours(node)) {
                if(!isVisited[edge.getDestinationNode()]) {
                    _dfs(graph, edge.getDestinationNode());
                }
            }
        };

        _dfs(graph, node);

        return traversalPath;
    }

    template<typename STDGraph, typename Edge>
    std::vector<std::int32_t> dfs(const STDGraph &graph, const std::int32_t &node, std::int32_t(*getDestinationNode)(const Edge &)) {
        std::vector<std::int32_t> traversalPath;
        traversalPath.reserve(graph.size());
        std::vector<bool> isVisited(graph.size());

        // core algorithm
        std::function<void(const STDGraph &, const std::int32_t &)> _dfs = nullptr;
        _dfs = [&getDestinationNode, &traversalPath, &isVisited, &_dfs](const STDGraph &graph, const std::int32_t &node) {
            if(isVisited[node]) return;

            isVisited[node] = true;
            traversalPath.emplace_back(node);
            for(auto edge: graph[node]) {
                if(!isVisited[getDestinationNode(edge)]) {
                    _dfs(graph, getDestinationNode(edge));
                }
            }
        };

        _dfs(graph, node);

        return traversalPath;
    }

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
