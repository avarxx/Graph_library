#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include <limits>
#include <vector>

#include "WeightedGraph.h"

namespace graph {

/**
 * @brief Реализация алгоритма Флойда-Уоршелла для поиска кратчайших путей между
 * всеми парами вершин.
 * @tparam VertexType Тип вершины (по умолчанию Vertex).
 * @tparam WeightType Тип веса ребра (по умолчанию int).
 * @param graph Взвешенный граф, по которому выполняется поиск.
 * @return Матрица расстояний между всеми парами вершин.
 */
template <typename VertexType = Vertex, typename WeightType = int>
std::vector<std::vector<WeightType>> FloydWarshall(
    const WeightedGraph<VertexType, WeightType>& graph) {
  const WeightType INF = std::numeric_limits<WeightType>::max();
  size_t n = graph.getVertices().size();
  std::vector<std::vector<WeightType>> distance(
      n, std::vector<WeightType>(n, INF));

  for (size_t i = 0; i < n; ++i) {
    distance[i][i] = 0;
  }

  for (const auto& edge : graph.getEdges()) {
    distance[edge.source.id][edge.target.id] = edge.weight;
  }

  for (size_t k = 0; k < n; ++k) {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
        if (distance[i][k] != INF && distance[k][j] != INF &&
            distance[i][k] + distance[k][j] < distance[i][j]) {
          distance[i][j] = distance[i][k] + distance[k][j];
        }
      }
    }
  }

  return distance;
}

}  // namespace graph

#endif  // FLOYDWARSHALL_H