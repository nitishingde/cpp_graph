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

    template<typename Edge>
    std::vector<std::int32_t> bfs(const Graph <Edge> &graph, const std::int32_t &node) {
        std::vector<std::int32_t> traversalPath;
        traversalPath.reserve(graph.size());
        std::vector<bool> isVisited(graph.size());
        std::deque<std::int32_t> queue;
        auto processNode = [&traversalPath, &isVisited, &queue](const std::int32_t &node) {
            traversalPath.emplace_back(node);
            isVisited[node] = true;
            queue.emplace_back(node);
        };

        //core algorithm
        processNode(node);
        for(; !queue.empty(); queue.pop_front()) {
            for(auto edge: graph.iterateNeighbours(queue.front())) {
                if(!isVisited[edge.getDestinationNode()]) {
                    processNode(edge.getDestinationNode());
                }
            }
        }

        return traversalPath;
    }

    template<typename STDGraph, typename Edge>
    std::vector<std::int32_t> bfs(const STDGraph &graph, const std::int32_t &node, std::int32_t(*getDestinationNode)(const Edge &)) {
        std::vector<std::int32_t> traversalPath;
        traversalPath.reserve(graph.size());
        std::vector<bool> isVisited(graph.size());
        std::deque<std::int32_t> queue;
        auto processNode = [&traversalPath, &isVisited, &queue](const std::int32_t &node) {
            traversalPath.emplace_back(node);
            isVisited[node] = true;
            queue.emplace_back(node);
        };

        //core algorithm
        processNode(node);
        for(; !queue.empty(); queue.pop_front()) {
            for(auto edge: graph[queue.front()]) {
                if(!isVisited[getDestinationNode(edge)]) {
                    processNode(getDestinationNode(edge));
                }
            }
        }

        return traversalPath;
    }
}

#endif //CPP_GRAPH_ALGOS_H
