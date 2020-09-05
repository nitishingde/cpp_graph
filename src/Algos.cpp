#include "Algos.h"

bool cpp_graph::isAncestor(
    const Node &ancestor,
    const Node &descendant,
    const std::vector<uint32_t> &timeIn,
    const std::vector<uint32_t> &timeOut
) {
    return (timeIn[ancestor] < timeIn[descendant] and timeOut[descendant] < timeOut[ancestor]);
}

bool cpp_graph::isDescendant(
    const Node &descendant,
    const Node &ancestor,
    const std::vector<uint32_t> &timeIn,
    const std::vector<uint32_t> &timeOut
) {
    return isAncestor(ancestor, descendant, timeIn, timeOut);
}