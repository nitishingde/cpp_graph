#ifndef CPP_GRAPH_GRAPH_H
#define CPP_GRAPH_GRAPH_H


#include <cstdint>
#include <vector>
#include <iterator>
#include <stdio.h>

#define COMPONENT_BASED_IMPLEMENTATION 0

namespace cpp_graph {
    enum Type {
        MATRIX = 0,
        LIST = 1,
        WEIGHTED = 2,
        DIRECTED = 4,
    };

#if COMPONENT_BASED_IMPLEMENTATION

    template<typename EdgeWeight = std::int8_t>
    class Graph {
/** Constants **/
    private:
    protected:
    public:

/** Data **/
    private:
        std::uint32_t mType;
        std::vector<std::vector<std::int32_t>> mNodeDataStore;
        std::vector<std::vector<EdgeWeight *>> mWeightDataStore;

        class Edge {
        private:
            int32_t mSourceNode;
            int32_t mDestinationNode;
            EdgeWeight *mpWeight;
        public:
            explicit Edge(const std::int32_t &sourceNode, const std::int32_t &destinationNode, EdgeWeight *pWeight = nullptr)
                : mSourceNode(sourceNode), mDestinationNode(destinationNode), mpWeight(pWeight) {
            }

            EdgeWeight *getWeight() {
                return this->mpWeight;
            }

            const EdgeWeight *getWeight() const {
                return this->mpWeight;
            }

            std::int32_t getSourceNode() {
                return this->mSourceNode;
            }

            std::int32_t getDestinationNode() {
                return this->mDestinationNode;
            }
        };

        class iterator {
        private:
            Graph<EdgeWeight> *mpGraph;
            const std::int32_t mNodeIndex;
            std::int32_t mIteratorIndex;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = Edge;
            using difference_type = std::int32_t;
            using pointer = Edge *;
            using reference = Edge &;

            explicit iterator(Graph<EdgeWeight> *pGraph, std::int32_t nodeIndex, std::int32_t startIndex)
                : mpGraph(pGraph), mNodeIndex(nodeIndex), mIteratorIndex(startIndex) {
                if(!pGraph->isAdjacencyList()) {
                    if(pGraph->isWeighted()) {
                        if(pGraph->mWeightDataStore[nodeIndex][startIndex] == nullptr) ++(*this);
                    } else {
                        if(pGraph->mNodeDataStore[nodeIndex][startIndex] == 0) ++(*this);
                    }
                }
            }

            // pre increment
            iterator &operator++() {
                if(this->mpGraph->isAdjacencyList()) {
                    if(this->mIteratorIndex < this->mpGraph->mNodeDataStore[this->mNodeIndex].size()) {
                        ++this->mIteratorIndex;
                    }
                } else {
                    if(this->mpGraph->isWeighted()) {
                        do {
                            ++this->mIteratorIndex;
                        } while(this->mIteratorIndex < this->mpGraph->size() and
                                this->mpGraph->mWeightDataStore[this->mNodeIndex][this->mIteratorIndex] == nullptr);
                    } else {
                        do {
                            ++this->mIteratorIndex;
                        } while(this->mIteratorIndex < this->mpGraph->size() and
                                this->mpGraph->mNodeDataStore[this->mNodeIndex][this->mIteratorIndex] == 0);
                    }
                }
                return *this;
            }

            // post increment
            iterator &operator++(int) {
                iterator ret(this->mpGraph, this->mNodeIndex, this->mIteratorIndex);
                ++(*this);
                return ret;
            }

            bool operator==(const iterator &other) const {
                return this->mNodeIndex == other.mNodeIndex and this->mIteratorIndex == other.mIteratorIndex;
            }

            bool operator!=(const iterator &other) const {
                return this->mNodeIndex != other.mNodeIndex || this->mIteratorIndex != other.mIteratorIndex;
            }

            value_type operator*() {
                return value_type(
                    this->mNodeIndex,
                    this->mpGraph->isAdjacencyList()? this->mpGraph->mNodeDataStore[this->mNodeIndex][this->mIteratorIndex]: this->mIteratorIndex,
                    this->mpGraph->isWeighted()? this->mpGraph->mWeightDataStore[this->mNodeIndex][this->mIteratorIndex]: nullptr
                );
            }
        };

        class Iterable {
            iterator *mpBegin = nullptr;
            iterator *mpEnd = nullptr;
            Graph<EdgeWeight> *mpGraph = nullptr;
            std::int32_t mNodeIndex;
        public:
            explicit Iterable(Graph<EdgeWeight> *pGraph, std::int32_t nodeIndex)
                : mpGraph(pGraph), mNodeIndex(nodeIndex) {
                if(pGraph->isWeighted()) {
                    this->mpBegin = new iterator(pGraph, nodeIndex, 0);
                    this->mpEnd = new iterator(pGraph, nodeIndex, pGraph->mWeightDataStore[nodeIndex].size());
                } else {
                    this->mpBegin = new iterator(pGraph, nodeIndex, 0);
                    this->mpEnd = new iterator(pGraph, nodeIndex, pGraph->mNodeDataStore[nodeIndex].size());
                }
            }

            ~Iterable() {
                delete this->mpBegin;
                this->mpBegin = nullptr;
                delete this->mpEnd;
                this->mpEnd = nullptr;
            }

            iterator& begin() {
                return *this->mpBegin;
            }

            iterator& begin() const {
                return *this->mpBegin;
            }

            iterator& end() {
                return *this->mpEnd;
            }

            iterator& end() const {
                return *this->mpEnd;
            }

            std::size_t size() const {
                if(this->mpGraph->isWeighted()) {
                    return this->mpGraph->mWeightDataStore[this->mNodeIndex].size();
                } else {
                    return this->mpGraph->mNodeDataStore[this->mNodeIndex].size();
                }
            }
        };

    protected:
    public:

/** Methods **/
    private:
        bool isAdjacencyList() const {
            return this->mType & LIST;
        }

        bool isWeighted() const {
            return this->mType & WEIGHTED;
        }

        bool isDirected() const {
            return this->mType & DIRECTED;
        }

    protected:
    public:

        explicit Graph(std::int32_t noOfNodes, std::uint32_t typeFlag = LIST | DIRECTED) noexcept {
            this->mType = typeFlag;
            if(this->isAdjacencyList()) {
                this->mNodeDataStore = std::vector<std::vector<std::int32_t>>(noOfNodes);
                if(this->isWeighted()) this->mWeightDataStore = std::vector<std::vector<EdgeWeight *>>(noOfNodes);
            } else {
                if(this->isWeighted()) {
                    this->mWeightDataStore = std::vector<std::vector<EdgeWeight *>>(
                        noOfNodes,
                        std::vector<EdgeWeight *>(noOfNodes, nullptr)
                    );
                } else {
                    this->mNodeDataStore = std::vector<std::vector<std::int32_t>>(
                        noOfNodes,
                        std::vector<std::int32_t>(noOfNodes,0)
                    );
                }
            }
        }

        Graph(const Graph<EdgeWeight> &other) = delete;

        Graph<EdgeWeight> &operator=(const Graph<EdgeWeight> &other) = delete;

        ~Graph() {
            if(this->isWeighted()) {
                std::uint8_t deletedWeights[this->mWeightDataStore.size()];
                memset(deletedWeights, 0, sizeof(deletedWeights));
                for(std::size_t node = 0; node < this->mWeightDataStore.size(); ++node) {
                    if(this->isAdjacencyList()) {
                        for(std::size_t otherNode = 0; otherNode < this->mWeightDataStore[node].size(); ++otherNode) {
                            if(!deletedWeights[this->mNodeDataStore[node][otherNode]]) {
                                delete this->mWeightDataStore[node][otherNode];
                            }
                            this->mWeightDataStore[node][otherNode] = nullptr;
                        }
                    } else {
                        for(std::size_t otherNode = 0; otherNode < 0; ++otherNode) {
                            if(!deletedWeights[otherNode]) {
                                delete this->mWeightDataStore[node][otherNode];
                            }
                            this->mWeightDataStore[node][otherNode] = nullptr;
                        }
                    }
                    deletedWeights[node] = true;
                }
            }
        }

        Iterable operator[](const std::int32_t &index) {
            return this->iterateNeighbours(index);
        }

        void addEdge(const std::int32_t &sourceNode, const std::int32_t &destinationNode, EdgeWeight *pWeight = nullptr) {
            if(this->isWeighted() and pWeight == nullptr) {
                throw "weight cannot be null in a weighted graph";
            }
            if(!this->isWeighted() and pWeight != nullptr) {
                delete pWeight;
                throw "weight has to be null in a unweighted graph";
            }

            auto _add_edge = [this](const std::int32_t &sourceNode, const std::int32_t &destinationNode, EdgeWeight *pWeight = nullptr) {
                if(this->isAdjacencyList()) {
                    this->mNodeDataStore[sourceNode].emplace_back(destinationNode);
                    if(this->isWeighted()) {
                        this->mWeightDataStore[sourceNode].emplace_back(pWeight);
                    }
                } else {
                    if(this->isWeighted()) {
                        this->mWeightDataStore[sourceNode][destinationNode] = pWeight;
                    } else {
                        this->mNodeDataStore[sourceNode][destinationNode] = 1;
                    }
                }
            };
            _add_edge(sourceNode, destinationNode, pWeight);
            if(!this->isDirected()) _add_edge(destinationNode, sourceNode, pWeight);
        }

        Iterable iterateNeighbours(const std::int32_t &nodeIndex) {
            return Iterable(this, nodeIndex);
        }

        std::size_t size() const {
            if(this->isWeighted()) {
                return this->mWeightDataStore.size();
            } else {
                return this->mNodeDataStore.size();
            }
        }
    };
#else

    template<typename EdgeWeight = std::int8_t>
    class Graph {
/** Constants **/
    private:
    protected:
    public:

/** Data **/
    private:
        class EdgeData {
        private:
            std::int32_t mOtherNode;
            EdgeWeight* mpWeight;
        public:
            explicit EdgeData(std::int32_t otherNode = -1, EdgeWeight* pWeight = nullptr)
                : mOtherNode(otherNode), mpWeight(pWeight) {
            }

            std::int32_t getDestinationNode() {
                return this->mOtherNode;
            }

            EdgeWeight* getWeight() {
                return this->mpWeight;
            }

            void setWeight(EdgeWeight* pWeight) {
                this->mpWeight = pWeight;
            }
        };

        std::uint32_t mType;
        std::vector<std::vector<std::int32_t>> mUnweightedAdjacencyList;
        std::vector<std::vector<std::uint8_t>> mUnweightedAdjacencyMatrix;
        std::vector<std::vector<EdgeData>> mWeightedAdjacencyList;
        std::vector<std::vector<EdgeWeight*>> mWeightedAdjacencyMatrix;

        class Edge {
        private:
            int32_t mSourceNode;
            int32_t mDestinationNode;
            EdgeWeight *mpWeight;
        public:
            explicit Edge(const std::int32_t &sourceNode, const std::int32_t &destinationNode, EdgeWeight *pWeight = nullptr)
                : mSourceNode(sourceNode), mDestinationNode(destinationNode), mpWeight(pWeight) {
            }

            EdgeWeight *getWeight() {
                return this->mpWeight;
            }

            const EdgeWeight *getWeight() const {
                return this->mpWeight;
            }

            std::int32_t getSourceNode() {
                return this->mSourceNode;
            }

            std::int32_t getDestinationNode() {
                return this->mDestinationNode;
            }
        };

        class iterator {
        private:
            Graph<EdgeWeight> *mpGraph;
            const std::int32_t mNodeIndex;
            std::int32_t mIteratorIndex;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = Edge;
            using difference_type = std::int32_t;
            using pointer = Edge *;
            using reference = Edge &;

            explicit iterator(Graph<EdgeWeight> *pGraph, std::int32_t nodeIndex, std::int32_t startIndex)
                : mpGraph(pGraph), mNodeIndex(nodeIndex), mIteratorIndex(startIndex) {
                if(!pGraph->isAdjacencyList()) {
                    if(pGraph->isWeighted()) {
                        if(pGraph->mWeightedAdjacencyMatrix[nodeIndex][startIndex] == nullptr) ++(*this);
                    } else {
                        if(pGraph->mUnweightedAdjacencyMatrix[nodeIndex][startIndex] == 0) ++(*this);
                    }
                }
            }

            // pre increment
            iterator &operator++() {
                if(this->mpGraph->isAdjacencyList()) {
                    if(this->mpGraph->isWeighted()) {
                        if(this->mIteratorIndex < this->mpGraph->mWeightedAdjacencyList[this->mNodeIndex].size()) {
                            ++this->mIteratorIndex;
                        }
                    } else {
                        if(this->mIteratorIndex < this->mpGraph->mUnweightedAdjacencyList[this->mNodeIndex].size()) {
                            ++this->mIteratorIndex;
                        }
                    }
                } else {
                    if(this->mpGraph->isWeighted()) {
                        do {
                            ++this->mIteratorIndex;
                        } while(this->mIteratorIndex < this->mpGraph->size() and
                                this->mpGraph->mWeightedAdjacencyMatrix[this->mNodeIndex][this->mIteratorIndex] == nullptr);
                    } else {
                        do {
                            ++this->mIteratorIndex;
                        } while(this->mIteratorIndex < this->mpGraph->size() and
                                this->mpGraph->mUnweightedAdjacencyMatrix[this->mNodeIndex][this->mIteratorIndex] == 0);
                    }
                }
                return *this;
            }

            // post increment
            iterator &operator++(int) {
                iterator ret(this->mpGraph, this->mNodeIndex, this->mIteratorIndex);
                ++(*this);
                return ret;
            }

            bool operator==(const iterator &other) const {
                return this->mNodeIndex == other.mNodeIndex and this->mIteratorIndex == other.mIteratorIndex;
            }

            bool operator!=(const iterator &other) const {
                return this->mNodeIndex != other.mNodeIndex || this->mIteratorIndex != other.mIteratorIndex;
            }

            value_type operator*() {
                if(this->mpGraph->isWeighted()) {
                    return value_type(
                        this->mNodeIndex,
                        this->mpGraph->isAdjacencyList()
                            ? this->mpGraph->mWeightedAdjacencyList[this->mNodeIndex][this->mIteratorIndex].getDestinationNode()
                            : this->mIteratorIndex,
                        this->mpGraph->isAdjacencyList()
                            ? this->mpGraph->mWeightedAdjacencyList[this->mNodeIndex][this->mIteratorIndex].getWeight()
                            : this->mpGraph->mWeightedAdjacencyMatrix[this->mNodeIndex][this->mIteratorIndex]
                    );
                } else {
                    return value_type(
                        this->mNodeIndex,
                        this->mpGraph->isAdjacencyList()
                            ? this->mpGraph->mUnweightedAdjacencyList[this->mNodeIndex][this->mIteratorIndex]
                            : this->mIteratorIndex,
                        nullptr
                    );
                }
            }
        };

        class Iterable {
            iterator *mpBegin = nullptr;
            iterator *mpEnd = nullptr;
            Graph<EdgeWeight> *mpGraph = nullptr;
            std::int32_t mNodeIndex;
        public:
            explicit Iterable(Graph<EdgeWeight> *pGraph, std::int32_t nodeIndex)
                : mpGraph(pGraph), mNodeIndex(nodeIndex) {
                if(pGraph->isWeighted()) {
                    this->mpBegin = new iterator(pGraph, nodeIndex, 0);
                    this->mpEnd = new iterator(
                        pGraph,
                        nodeIndex,
                        pGraph->isAdjacencyList()? pGraph->mWeightedAdjacencyList[nodeIndex].size()
                            : pGraph->mWeightedAdjacencyMatrix.size()
                    );
                } else {
                    this->mpBegin = new iterator(pGraph, nodeIndex, 0);
                    this->mpEnd = new iterator(
                        pGraph,
                        nodeIndex,
                        pGraph->isAdjacencyList()? pGraph->mUnweightedAdjacencyList[nodeIndex].size()
                            : pGraph->mUnweightedAdjacencyMatrix.size()
                    );
                }
            }

            ~Iterable() {
                delete this->mpBegin;
                this->mpBegin = nullptr;
                delete this->mpEnd;
                this->mpEnd = nullptr;
            }

            iterator& begin() {
                return *this->mpBegin;
            }

            iterator& begin() const {
                return *this->mpBegin;
            }

            iterator& end() {
                return *this->mpEnd;
            }

            iterator& end() const {
                return *this->mpEnd;
            }

            std::size_t size() const {
                if(this->mpGraph->isWeighted()) {
                    if(this->mpGraph->isAdjacencyList()) {
                        return this->mpGraph->mWeightedAdjacencyList[this->mNodeIndex].size();
                    } else {
                        return this->mpGraph->mWeightedAdjacencyMatrix.size();
                    }
                } else {
                    if(this->mpGraph->isAdjacencyList()) {
                        return this->mpGraph->mUnweightedAdjacencyList[this->mNodeIndex].size();
                    } else {
                        return this->mpGraph->mUnweightedAdjacencyMatrix[this->mNodeIndex].size();
                    }
                }
            }
        };

    protected:
    public:

/** Methods **/
    private:
        bool isAdjacencyList() const {
            return this->mType & LIST;
        }

        bool isWeighted() const {
            return this->mType & WEIGHTED;
        }

        bool isDirected() const {
            return this->mType & DIRECTED;
        }

    protected:
    public:
        explicit Graph(std::int32_t noOfNodes, std::uint32_t typeFlag = LIST | DIRECTED) noexcept {
            this->mType = typeFlag;
            if(this->isWeighted()) {
                if(this->isAdjacencyList()) {
                    this->mWeightedAdjacencyList = std::vector<std::vector<EdgeData>>(noOfNodes);
                } else {
                    this->mWeightedAdjacencyMatrix = std::vector<std::vector<EdgeWeight*>>(
                        noOfNodes,
                        std::vector<EdgeWeight*>(noOfNodes, nullptr)
                    );
                }
            } else {
                if(this->isAdjacencyList()) {
                    this->mUnweightedAdjacencyList = std::vector<std::vector<std::int32_t>>(noOfNodes);
                } else {
                    this->mUnweightedAdjacencyMatrix = std::vector<std::vector<std::uint8_t>>(
                        noOfNodes,
                        std::vector<std::uint8_t>(noOfNodes, 0)
                    );
                }
            }
        }

        Graph(const Graph<EdgeWeight> &other) = delete;

        Graph<EdgeWeight> &operator=(const Graph<EdgeWeight> &other) = delete;

        ~Graph() {
            if(this->isWeighted()) {
                std::uint8_t deletedWeights[this->mWeightedAdjacencyList.size()];
                memset(deletedWeights, 0, sizeof(deletedWeights));
                if(this->isAdjacencyList()) {
                    for(std::size_t node = 0; node < this->mWeightedAdjacencyList.size(); ++node) {
                        for(std::size_t i = 0; i < this->mWeightedAdjacencyList[node].size(); ++i) {
                            if(!deletedWeights[this->mWeightedAdjacencyList[node][i].getDestinationNode()]) {
                                delete this->mWeightedAdjacencyList[node][i].getWeight();
                            }
                            this->mWeightedAdjacencyList[node][i].setWeight(nullptr);
                        }
                        deletedWeights[node] = true;
                    }
                } else {
                    for(std::size_t node = 0; node < this->mWeightedAdjacencyMatrix.size(); ++node) {
                        for(std::size_t otherNode = 0; otherNode < this->mWeightedAdjacencyMatrix.size(); ++otherNode) {
                            if(!deletedWeights[otherNode]) {
                                delete this->mWeightedAdjacencyMatrix[node][otherNode];
                            }
                            this->mWeightedAdjacencyMatrix[node][otherNode] = nullptr;
                        }
                        deletedWeights[node] = true;
                    }
                }
            }
        }

        Iterable operator[](const std::int32_t &index) {
            return this->iterateNeighbours(index);
        }

        void addEdge(const std::int32_t &sourceNode, const std::int32_t &destinationNode, EdgeWeight *pWeight = nullptr) {
            if(this->isWeighted() and pWeight == nullptr) {
                throw "weight cannot be null in a weighted graph";
            }
            if(!this->isWeighted() and pWeight != nullptr) {
                delete pWeight;
                throw "weight has to be null in a unweighted graph";
            }

            auto _add_edge = [this](const std::int32_t &sourceNode, const std::int32_t &destinationNode, EdgeWeight *pWeight = nullptr) {
                if(this->isWeighted()) {
                    if(this->isAdjacencyList()) {
                        this->mWeightedAdjacencyList[sourceNode].emplace_back(EdgeData(destinationNode, pWeight));
                    } else {
                        this->mWeightedAdjacencyMatrix[sourceNode][destinationNode] = pWeight;
                    }
                } else {
                    if(this->isAdjacencyList()) {
                        this->mUnweightedAdjacencyList[sourceNode].emplace_back(destinationNode);
                    } else {
                        this->mUnweightedAdjacencyMatrix[sourceNode][destinationNode] = 1;
                    }
                }
            };
            _add_edge(sourceNode, destinationNode, pWeight);
            if(!this->isDirected()) _add_edge(destinationNode, sourceNode, pWeight);
        }

        Iterable iterateNeighbours(const std::int32_t &nodeIndex) {
            return Iterable(this, nodeIndex);
        }

        std::size_t size() const {
            if(this->isWeighted()) {
                if(this->isAdjacencyList()) {
                    return this->mWeightedAdjacencyList.size();
                } else {
                    return this->mWeightedAdjacencyMatrix.size();
                }
            } else {
                if(this->isAdjacencyList()) {
                    return this->mUnweightedAdjacencyList.size();
                } else {
                    return this->mUnweightedAdjacencyMatrix.size();
                }
            }
        }
    };
#endif
}

#endif //CPP_GRAPH_GRAPH_H
