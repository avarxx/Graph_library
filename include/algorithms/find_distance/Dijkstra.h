#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits>
#include <queue>
#include <vector>

#include "WeightedGraph.h"

namespace graph {

/**
 * @brief Реализация алгоритма Дейкстры для поиска кратчайших путей.
 * @tparam VertexType Тип вершины (по умолчанию Vertex).
 * @tparam WeightType Тип веса ребра (по умолчанию int).
 * @param graph Взвешенный граф, по которому выполняется поиск.
 * @param start Начальная вершина для поиска кратчайших путей.
 * @return Вектор расстояний, где индекс соответствует id вершины.
 */
template <typename VertexType = Vertex, typename WeightType = int>
std::vector<WeightType> Dijkstra(WeightedGraph<VertexType, WeightType>& graph,
                                 const VertexType& start) {
  const WeightType INF = std::numeric_limits<WeightType>::max();
  size_t numVertices = graph.getVertices().size();
  std::vector<WeightType> distances(numVertices, INF);
  distances[start.id] = 0;

  auto cmp = [](const std::pair<WeightType, VertexType>& left,
                const std::pair<WeightType, VertexType>& right) {
    return left.first > right.first;
  };
  std::priority_queue<std::pair<WeightType, VertexType>,
                      std::vector<std::pair<WeightType, VertexType>>,
                      decltype(cmp)>
      pq(cmp);
  pq.push({0, start});

  while (!pq.empty()) {
    VertexType u = pq.top().second;
    WeightType dist_u = pq.top().first;
    pq.pop();

    if (dist_u > distances[u.id]) continue;

    for (auto& v : graph.getAdjacencyVertices(u)) {
      WeightType weight = graph.getEdgeWeight(u, v);
      if (distances[u.id] + weight < distances[v.id]) {
        distances[v.id] = distances[u.id] + weight;
        pq.push({distances[v.id], v});
      }
    }
  }

  return distances;
}

}  // namespace graph

#endif  // DIJKSTRA_H