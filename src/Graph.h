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

    bool operator<(const Node<Edge> &other) const {
        return *this->mpEdge < *other.mpEdge;
    }

    operator int() const {
        return mIndex;
    }

    int getIndex() const {
        return mIndex;
    }

    operator bool() const {
        return this->isValid();
    }

    bool isValid() const {
        return this->mpEdge != nullptr;
    }
};

template<typename Edge>
class Graph {
public:
    enum Type {
        ADJACENCY_LIST,
        ADJACENCY_MATRIX
    };
    Type mType = ADJACENCY_LIST;
    std::vector<std::vector<Node<Edge>>> mDataStore;

    Graph(std::int32_t noOfNodes, Type type = ADJACENCY_LIST) noexcept {
        this->mType = type;
        switch(type) {
            case ADJACENCY_LIST:
                this->mDataStore = std::vector<std::vector<Node<Edge>>>(noOfNodes, std::vector<Node<Edge>>());
                break;
            case ADJACENCY_MATRIX:
                this->mDataStore = std::vector<std::vector<Node<Edge>>>(noOfNodes, std::vector<Node<Edge>>(noOfNodes));
                for(auto &nodeList: this->mDataStore)
                    for(std::uint32_t i = 0; i < nodeList.size(); ++i)
                        nodeList[i].mIndex = i;
                break;
        }
    }

    Graph(const Graph<Edge> &other) = delete;
    Graph<Edge>& operator=(const Graph<Edge> &other) = delete;

    Graph(std::vector<std::vector<Node<Edge>>> &&graph) noexcept
        : mDataStore(std::move(graph)) {
        this->mType = ADJACENCY_LIST;
    }

    Graph(Graph<Edge> &&other) noexcept
        : mType(other.mType)
        , mDataStore(std::move(other.mDataStore)) {
    }

    Graph<Edge>& operator=(Graph<Edge> &&other) noexcept {
        this->mType = other.mType;
        this->mDataStore = std::move(other.mDataStore);
    }

    std::vector<Node<Edge>>& operator[](std::int32_t index) {
        return this->mDataStore[index];
    }

    const std::vector<Node<Edge>>& operator[](std::int32_t index) const {
        return this->mDataStore[index];
    }

    auto& getDataStore() {
        return this->mDataStore;
    }

    auto& getDataStore() const {
        return this->mDataStore;
    }

    std::vector<Node<Edge>>& getNeighbours(const std::int32_t &node_index) {
        return this->mDataStore[node_index];
    }

    const std::vector<Node<Edge>>& getNeighbours(const std::int32_t &node_index) const {
        return this->mDataStore[node_index];
    }

    std::size_t size() const {
        return this->mDataStore.size();
    }
};


#endif //CPP_GRAPH_GRAPH_H
