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
  std::stack<Vertex> stack;  // Стек для DFS.
  std::unordered_set<Vertex> visited;  // Множество посещённых вершин.

  // Начинаем с начальной вершины.
  stack.push(startVertex);
  visited.insert(startVertex);

  while (!stack.empty()) {
    Vertex currentVertex = stack.top();
    stack.pop();

    // Обрабатываем текущую вершину.
    visitor.visitVertex(currentVertex);

    // Получаем соседей текущей вершины.
    auto neighbors = graph.getAdjacencyVertices(currentVertex);
    for (auto& vertex : neighbors) {
      // Исследуем ребро между текущей вершиной и соседом.
      visitor.examineEdge(EdgeType(currentVertex, vertex));

      // Если соседняя вершина ещё не посещена, добавляем её в стек.
      if (visited.find(vertex) == visited.end()) {
        visited.insert(vertex);
        stack.push(vertex);

        // Обрабатываем ребро, добавленное в дерево поиска.
        visitor.treeEdge(EdgeType(currentVertex, vertex));
      }
    }

    // Завершаем обработку текущей вершины.
    visitor.finishVertex(currentVertex);
  }

  // Возвращаем множество посещённых вершин.
  return visited;
}

}  // namespace graph

#endif  // DFS_H