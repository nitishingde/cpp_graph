#ifndef CPP_GRAPH_ALGOS_H
#define CPP_GRAPH_ALGOS_H


#include "Graph.h"
#include <vector>
#include <deque>

template <typename Edge>
std::vector<std::int32_t> dfs(const Graph<Edge> &graph, const std::int32_t &node) {
    std::vector<std::int32_t> traversalPath;
    traversalPath.reserve(graph.size());
    std::vector<bool> isVisited(graph.size());

    // core algorithm
    std::function<void(const Graph<Edge>&, const std::int32_t&)> _dfs = nullptr;
    _dfs = [&traversalPath, &isVisited, &_dfs](const Graph<Edge> &graph, const std::int32_t &node) {
        if(isVisited[node]) return;

        isVisited[node] = true;
        traversalPath.emplace_back(node);
        for(auto &neighbour: graph.getNeighbours(node)) {
            if(!isVisited[neighbour.getIndex()]) {
                _dfs(graph, neighbour.getIndex());
            }
        }
    };

    _dfs(graph, node);

    return traversalPath;
}

template<typename Edge>
std::vector<std::int32_t> bfs(const Graph<Edge> &graph, const std::int32_t &node) {
    std::vector<std::int32_t> traversalPath;
    traversalPath.reserve(graph.size());
    std::vector<bool> isVisited(graph.mDataStore.size());
    std::deque<std::int32_t> queue;
    auto processNode = [&traversalPath, &isVisited, &queue](const std::int32_t &node) {
        traversalPath.emplace_back(node);
        isVisited[node] = true;
        queue.emplace_back(node);
    };

    //core algorithm
    processNode(node);
    for(; !queue.empty(); queue.pop_front()) {
        for(auto &neighbour: graph.getNeighbours(queue.front())) {
            if(!isVisited[neighbour.getIndex()]) {
                processNode(neighbour.getIndex());
            }
        }
    }

    return traversalPath;
}


#endif //CPP_GRAPH_ALGOS_H
