#ifndef CPP_GRAPH_GRAPH_H
#define CPP_GRAPH_GRAPH_H


#include <cstdint>
#include <vector>

template <typename Edge>
class Node {
public:
    std::int32_t mIndex;
    Edge *mpEdge = nullptr;

    Node(const int32_t &index = 0, Edge *edge = nullptr) noexcept
        : mIndex(index)
        , mpEdge(edge) {
    }

    Node(const Node<Edge> &other) {
        this->mIndex = other.mIndex;
        this->mpEdge = new Edge(*other.mpEdge);
    }

    Node<Edge>& operator=(const Node<Edge> &other) noexcept {
        this->mIndex = other.mIndex;
        this->mpEdge = new Edge(*other.mpEdge);
    }

    Node(Node<Edge> &&other) noexcept {
        this->mIndex = other.mIndex;
        this->mpEdge = other.mpEdge;
        other.mpEdge = nullptr;
    }

    Node<Edge>& operator=(Node<Edge> &&other) {
        this->mIndex = other.mIndex;
        this->mpEdge = other.mpEdge;
        other.mpEdge = nullptr;
    }

    ~Node() noexcept {
        delete this->mpEdge;
        this->mpEdge = nullptr;
    }

    bool operator<(const Node<Edge> &other) {
        return *this->mpEdge < *other.mpEdge;
    }

    operator int() {
        return mIndex;
    }

    int getIndex() {
        return mIndex;
    }
};

template<typename Edge>
class Graph {
public:
    std::vector<std::vector<Node<Edge>>> mDataStore;

    Graph(std::int32_t noOfNodes) noexcept {
        mDataStore = std::vector<std::vector<Node<Edge>>>(noOfNodes, std::vector<Node<Edge>>());
    }

    Graph(const Graph<Edge> &other) = delete;
    Graph<Edge>& operator=(const Graph<Edge> &other) = delete;

    Graph(std::vector<std::vector<Node<Edge>>> &&graph) noexcept
        : mDataStore(std::move(graph)) {
    }

    Graph(Graph<Edge> &&other) noexcept
        : mDataStore(std::move(other.mDataStore)) {
    }

    Graph<Edge>& operator=(Graph<Edge> &&other) noexcept {
        this->mDataStore = std::move(other.mDataStore);
    }

    std::vector<Node<Edge>>& operator[](std::int32_t index) {
        return this->mDataStore[index];
    }

    auto& getDataStore() {
        return this->mDataStore;
    }

    std::vector<Node<Edge>>& getNeighbours(const std::int32_t &node_index) {
        return this->mDataStore[node_index];
    }
};


#endif //CPP_GRAPH_GRAPH_H
