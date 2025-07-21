#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "Graph.h"

namespace graph {

/**
 * @brief Алгоритм Беллмана-Форда для поиска кратчайших путей от одной вершины
 * до всех остальных.
 * @tparam VertexType Тип вершины.
 * @tparam WeightType Тип веса ребра.
 * @param graph Граф.
 * @param start Начальная вершина.
 * @return Карта расстояний от начальной вершины до всех остальных.
 * @throws std::runtime_error Если граф содержит отрицательный цикл.
 */
template <typename VertexType, typename WeightType>
std::unordered_map<VertexType, WeightType> BellmanFord(
    const Graph<VertexType, WeightedEdge<WeightType>>& graph,
    const VertexType& start) {
  std::unordered_map<VertexType, WeightType> distances;
  for (const auto& vertex : graph.getVertices()) {
    distances[vertex] = std::numeric_limits<WeightType>::max();
  }
  distances[start] = 0;

  for (size_t i = 0; i < graph.getVertices().size() - 1; ++i) {
    for (const auto& edge : graph.getEdges()) {
      if (distances[edge.source] != std::numeric_limits<WeightType>::max() &&
          distances[edge.source] + edge.weight < distances[edge.target]) {
        distances[edge.target] = distances[edge.source] + edge.weight;
      }
    }
  }

  for (const auto& edge : graph.getEdges()) {
    if (distances[edge.source] != std::numeric_limits<WeightType>::max() &&
        distances[edge.source] + edge.weight < distances[edge.target]) {
      throw std::runtime_error("Граф содержит отрицательный цикл");
    }
  }

  return distances;
}

}  // namespace graph

#endif  // BELLMAN_FORD_H