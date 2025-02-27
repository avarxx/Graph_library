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

        // Посещаем вершину
        visitor.visitVertex(graph.getVertex(currentVertex));

        // Обходим соседей
        auto neighbors = graph.getNeighborsIterator(currentVertex);
        while (neighbors != graph.getNeighborsIterator(currentVertex + 1)) {  // Условный конец итератора
            int neighbor = *neighbors;

            // Обнаружение ребра
            visitor.examineEdge(EdgeType(currentVertex, neighbor));

            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push(neighbor);

                // Ребро дерева
                visitor.treeEdge(EdgeType(currentVertex, neighbor));
            }

            ++neighbors;
        }

        // Завершение обработки вершины
        visitor.finishVertex(graph.getVertex(currentVertex));
    }
}

}  // namespace graph

#endif  // BFS_H