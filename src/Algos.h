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

    /** -----------------------------------------------------------------------------std containers----------------------------------------------------------------------------- **/

    /**
     * Find if a node is a ancestor of other node from timeIn and timeOut data
     * @param ancestor cpp_graph::Node
     * @param descendant cpp_graph::Node
     * @param timeIn
     * @param timeOut
     * @return bool
     */
    bool isAncestor(const Node &ancestor, const Node &descendant, const std::vector<uint32_t> &timeIn, const std::vector<uint32_t> &timeOut);

    /**
     * Find if a node is a descendant of other node from timeIn and timeOut data
     * @param descendant cpp_graph::Node
     * @param ancestor cpp_graph::Node
     * @param timeIn
     * @param timeOut
     * @return bool
     */
    bool isDescendant(const Node &descendant, const Node &ancestor, const std::vector<uint32_t> &timeIn, const std::vector<uint32_t> &timeOut);

    /**
     * Depth First Search on graph represented by std containers
     * @tparam Graph 2d std container
     * @param graph adjacency list
     * @param node cpp_graph::Node
     * @param getDestinationNode lambda function that extracts the destination node from GraphDatum
     * @return tuple(std::vector<uint32_t> timeIn, std::vector<uint32_t> timeOut)
     */
    template<typename Graph, typename InnerContainer = typename Graph::value_type, typename GraphDatum = typename InnerContainer::value_type>
    auto dfs(const Graph &graph, const Node &node, Node(*getDestinationNode)(const typename InnerContainer::value_type &)) {
        std::vector<uint32_t> timeIn(graph.size(), 0);
        std::vector<uint32_t> timeOut(graph.size(), 0);
        uint32_t timer = 0;
        std::vector<DfsColour> colour(graph.size(), DfsColour::WHITE);

        // core algorithm
        std::function<void(const Graph &, const Node &)> _dfs = nullptr;
        _dfs = [&getDestinationNode, &timeIn, &timeOut, &timer, &colour, &_dfs](const Graph &graph, const Node &node) {
            timeIn[node] = timer++;
            colour[node] = DfsColour::GRAY;
            for(const GraphDatum &graphDatum: graph[node]) {
                if(auto destinationNode = getDestinationNode(graphDatum); colour[destinationNode] == DfsColour::WHITE) {
                    _dfs(graph, destinationNode);
                }
            }
            timeOut[node] = timer++;
            colour[node] = DfsColour::BLACK;
        };

        _dfs(graph, node);

        return std::make_tuple(timeIn, timeOut);
    }

    /**
     * Breadth First Search on graph represented by std containers
     * @tparam Graph 2d std container
     * @param graph adjacency list
     * @param node cpp_graph::Node
     * @param getDestinationNode lambda function that extracts the destination node from GraphDatum
     * @return tuple(std::vector<cpp_graph::Node> parents, std::vector<uint32_t> distances)
     */
    template<typename Graph, typename InnerContainer = typename Graph::value_type, typename GraphDatum = typename InnerContainer::value_type>
    auto bfs(const Graph &graph, const Node &node, Node(*getDestinationNode)(const typename InnerContainer::value_type &)) {
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
            for(const auto &graphDatum: graph[sourceNode]) {
                if(auto destinationNode = getDestinationNode(graphDatum); !isNodeVisited(destinationNode)) {
                    processNode(destinationNode, sourceNode);
                }
            }
        }
        return std::make_tuple(parents, distances);
    }
}

#endif //CPP_GRAPH_ALGOS_H
