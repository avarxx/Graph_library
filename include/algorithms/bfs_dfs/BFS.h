#ifndef BFS_H
#define BFS_H

#include <iostream>
#include <queue>
#include <unordered_set>

#include "Graph.h"
#include "Visitor.h"

namespace graph {

/**
 * @brief Реализация алгоритма поиска в ширину (BFS).
 * @tparam VertexType Тип вершины.
 * @tparam EdgeType Тип ребра.
 * @param graph Граф, по которому выполняется поиск.
 * @param startVertex Начальная вершина для поиска.
 * @param visitor Посетитель (Visitor), который обрабатывает события BFS.
 * @return Вектор расстояний от начальной вершины до всех остальных вершин.
 */
template <typename VertexType, typename EdgeType>
std::vector<int> BFS(Graph<VertexType, EdgeType>& graph,
                     const Vertex& startVertex,
                     Visitor<VertexType, EdgeType>& visitor) {
  std::queue<VertexType> queue;  // Очередь для BFS.
  std::unordered_set<VertexType> visited;  // Множество посещённых вершин.
  std::vector<int> d(graph.getVertices().size() + 1, 0);  // Вектор расстояний.

  // Начинаем с начальной вершины.
  queue.push(startVertex);
  visited.insert(startVertex);

  while (!queue.empty()) {
    VertexType currentVertex = queue.front();
    queue.pop();

    // Обрабатываем текущую вершину.
    visitor.visitVertex(currentVertex);

    // Получаем соседей текущей вершины.
    auto neighbors = graph.getAdjacencyVertices(currentVertex);
    for (auto& vertex : neighbors) {
      // Исследуем ребро между текущей вершиной и соседом.
      visitor.examineEdge(EdgeType(currentVertex, vertex));

      // Если соседняя вершина ещё не посещена, добавляем её в очередь.
      if (visited.find(vertex) == visited.end()) {
        visited.insert(vertex);
        queue.push(vertex);
        d[vertex.id] = d[currentVertex.id] + 1;  // Обновляем расстояние.

        // Обрабатываем ребро, добавленное в дерево поиска.
        visitor.treeEdge(EdgeType(currentVertex, vertex));
      }
    }

    // Завершаем обработку текущей вершины.
    visitor.finishVertex(currentVertex);
  }

  // Возвращаем вектор расстояний.
  return d;
}

}  // namespace graph

#endif  // BFS_H