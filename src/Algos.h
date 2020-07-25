#ifndef CPP_GRAPH_ALGOS_H
#define CPP_GRAPH_ALGOS_H


#include "Graph.h"
#include <vector>

template <typename Edge>
std::vector<std::int32_t> dfs(const Graph<Edge> &graph, const std::int32_t &node) {
    std::vector<std::int32_t> traversalPath;
    traversalPath.reserve(graph.mDataStore.size());
    std::vector<bool> isVisited(graph.mDataStore.size());

    // core algorithm
    std::function<void(const Graph<Edge>&,std::int32_t)> _dfs = nullptr;
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



#endif //CPP_GRAPH_ALGOS_H
