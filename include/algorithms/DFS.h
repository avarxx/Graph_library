#ifndef DFS_H
#define DFS_H

#include "Graph.h"
#include "DFSVisitor.h"
#include <stack>
#include <unordered_set>

namespace graph {

template <typename VertexType, typename EdgeType>
void DFS(const Graph<VertexType, EdgeType>& graph, int startVertex, DFSVisitor<VertexType, EdgeType>& visitor) {
    std::stack<int> stack;
    std::unordered_set<int> visited;

    stack.push(startVertex);
    visited.insert(startVertex);

    while (!stack.empty()) {
        int currentVertex = stack.top();
        stack.pop();

        visitor.visitVertex(graph.getVertex(currentVertex));

        auto neighbors = graph.getNeighborsIterator(currentVertex);
        while (neighbors != graph.getNeighborsIterator(currentVertex + 1)) {  =
            int neighbor = *neighbors;

            visitor.examineEdge(EdgeType(currentVertex, neighbor));

            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                stack.push(neighbor);

                visitor.treeEdge(EdgeType(currentVertex, neighbor));
            }

            ++neighbors;
        }

        visitor.finishVertex(graph.getVertex(currentVertex));
    }
}

}  // namespace graph

#endif  // DFS_H