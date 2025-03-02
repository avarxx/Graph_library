#ifndef DFS_H
#define DFS_H

#include <stack>
#include <unordered_set>

#include "Graph.h"
#include "Visitor.h"

namespace graph {

/**
 * @brief Реализация алгоритма поиска в глубину (DFS).
 * @tparam VertexType Тип вершины.
 * @tparam EdgeType Тип ребра.
 * @param graph Граф, по которому выполняется поиск.
 * @param startVertex Начальная вершина для поиска.
 * @param visitor Посетитель (Visitor), который обрабатывает события DFS.
 * @return Множество посещённых вершин.
 */
template <typename VertexType, typename EdgeType>
std::unordered_set<Vertex> DFS(Graph<VertexType, EdgeType>& graph,
                               const Vertex& startVertex,
                               Visitor<VertexType, EdgeType>& visitor) {
  std::stack<Vertex> stack;  
  std::unordered_set<Vertex> visited;  

  stack.push(startVertex);
  visited.insert(startVertex);

  while (!stack.empty()) {
    Vertex currentVertex = stack.top();
    stack.pop();

    visitor.visitVertex(currentVertex);

    auto neighbors = graph.getAdjacencyVertices(currentVertex);
    for (auto& vertex : neighbors) {
      visitor.examineEdge(EdgeType(currentVertex, vertex));

      if (visited.find(vertex) == visited.end()) {
        visited.insert(vertex);
        stack.push(vertex);

        visitor.treeEdge(EdgeType(currentVertex, vertex));
      }
    }

    visitor.finishVertex(currentVertex);
  }

  return visited;
}

}  // namespace graph

#endif  // DFS_H