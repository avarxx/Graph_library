#ifndef BFS_H
#define BFS_H

#include "Graph.h"
#include "BFSVisitor.h"
#include <queue>
#include <unordered_set>

namespace graph {

template <typename VertexType, typename EdgeType>
void BFS(const Graph<VertexType, EdgeType>& graph, int startVertex, BFSVisitor<VertexType, EdgeType>& visitor) {
    std::queue<int> queue;
    std::unordered_set<int> visited;

    queue.push(startVertex);
    visited.insert(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();

        visitor.visitVertex(graph.getVertex(currentVertex));

        auto neighbors = graph.getNeighborsIterator(currentVertex);
        while (neighbors != graph.getNeighborsIterator(currentVertex + 1)) {  // Условный конец итератора
            int neighbor = *neighbors;

            visitor.examineEdge(EdgeType(currentVertex, neighbor));

            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push(neighbor);

                visitor.treeEdge(EdgeType(currentVertex, neighbor));
            }

            ++neighbors;
        }

        visitor.finishVertex(graph.getVertex(currentVertex));
    }
}

}  // namespace graph

#endif  // BFS_H