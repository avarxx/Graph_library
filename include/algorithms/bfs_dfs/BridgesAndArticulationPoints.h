#ifndef BRIDGES_AND_ARTICULATION_POINTS_H
#define BRIDGES_AND_ARTICULATION_POINTS_H

#include <unordered_map>
#include <vector>

#include "Graph.h"

namespace graph {

/**
 * @brief Класс для поиска мостов и точек сочленения в графе.
 * @tparam VertexType Тип вершины.
 * @tparam EdgeType Тип ребра.
 */
template <typename VertexType, typename EdgeType>
class BridgesAndArticulationPoints {
 public:
  /**
   * @brief Конструктор класса.
   * @param graph Граф, в котором ищутся мосты и точки сочленения.
   */
  BridgesAndArticulationPoints(Graph<VertexType, EdgeType> graph)
      : graph(graph), time(0) {}

  /**
   * @brief Поиск всех мостов в графе.
   * @return Вектор рёбер, являющихся мостами.
   */
  std::vector<EdgeType> findBridges() {
    std::vector<EdgeType> bridges;  // Вектор для хранения мостов.
    std::unordered_map<int, int> discoveryTime;  // Время обнаружения вершин.
    std::unordered_map<int, int> low;  // Минимальное время достижимости.
    std::unordered_map<int, int> parent;  // Родительские вершины.

    // Обход всех вершин графа.
    for (const auto& vertex : graph.getVertices()) {
      if (discoveryTime.find(vertex.id) == discoveryTime.end()) {
        dfsBridges(vertex, discoveryTime, low, parent, bridges);
      }
    }

    return bridges;
  }

  /**
   * @brief Поиск всех точек сочленения в графе.
   * @return Вектор идентификаторов вершин, являющихся точками сочленения.
   */
  std::vector<int> findArticulationPoints() {
    std::vector<int> articulationPoints;
    std::unordered_map<int, int> discoveryTime;
    std::unordered_map<int, int> low;
    std::unordered_map<int, int> parent;

    // Обход всех вершин графа.
    for (const auto& vertex : graph.getVertices()) {
      if (discoveryTime.find(vertex.id) == discoveryTime.end()) {
        dfsArticulationPoints(vertex, discoveryTime, low, parent,
                              articulationPoints);
      }
    }

    return articulationPoints;
  }

 private:
  Graph<VertexType, EdgeType> graph;  ///< Граф для анализа.
  int time;  ///< Время обнаружения вершин (используется в DFS).

  /**
   * @brief Вспомогательная функция для поиска мостов с использованием DFS.
   * @param u Текущая вершина.
   * @param discoveryTime Время обнаружения вершин.
   * @param low Минимальное время достижимости.
   * @param parent Родительские вершины.
   * @param bridges Вектор для хранения найденных мостов.
   */
  void dfsBridges(const Vertex& u, std::unordered_map<int, int>& discoveryTime,
                  std::unordered_map<int, int>& low,
                  std::unordered_map<int, int>& parent,
                  std::vector<EdgeType>& bridges) {
    discoveryTime[u.id] = low[u.id] = ++time;

    // Обход всех соседей текущей вершины.
    for (auto& v : graph.getAdjacencyVertices(u)) {
      if (discoveryTime.find(v.id) == discoveryTime.end()) {
        parent[v.id] = u.id;
        dfsBridges(v, discoveryTime, low, parent, bridges);

        // Обновляем минимальное время достижимости.
        low[u.id] = std::min(low[u.id], low[v.id]);

        // Если условие для моста выполнено, добавляем ребро в список мостов.
        if (low[v.id] > discoveryTime[u.id]) {
          bridges.push_back(EdgeType(u, v));
        }
      } else if (v.id != parent[u.id]) {
        // Обновляем минимальное время достижимости.
        low[u.id] = std::min(low[u.id], discoveryTime[v.id]);
      }
    }
  }

  /**
   * @brief Вспомогательная функция для поиска точек сочленения с использованием
   * DFS.
   * @param u Текущая вершина.
   * @param discoveryTime Время обнаружения вершин.
   * @param low Минимальное время достижимости.
   * @param parent Родительские вершины.
   * @param articulationPoints Вектор для хранения найденных точек сочленения.
   */
  void dfsArticulationPoints(const Vertex& u,
                             std::unordered_map<int, int>& discoveryTime,
                             std::unordered_map<int, int>& low,
                             std::unordered_map<int, int>& parent,
                             std::vector<int>& articulationPoints) {
    discoveryTime[u.id] = low[u.id] = ++time;
    int children = 0;  // Количество потомков в DFS-дереве.

    // Обход всех соседей текущей вершины.
    for (auto& v : graph.getAdjacencyVertices(u)) {
      if (discoveryTime.find(v.id) == discoveryTime.end()) {
        children++;
        parent[v.id] = u.id;
        dfsArticulationPoints(v, discoveryTime, low, parent,
                              articulationPoints);

        // Обновляем минимальное время достижимости.
        low[u.id] = std::min(low[u.id], low[v.id]);

        // Если вершина является корнем и имеет более одного потомка, это точка
        // сочленения.
        if (parent.find(u.id) == parent.end() && children > 1) {
          articulationPoints.push_back(u.id);
        }

        // Если вершина не является корнем и имеет потомка с low[v.id] >=
        // discoveryTime[u.id], это точка сочленения.
        if (parent.find(u.id) != parent.end() &&
            low[v.id] >= discoveryTime[u.id]) {
          articulationPoints.push_back(u.id);
        }
      } else if (v.id != parent[u.id]) {
        // Обновляем минимальное время достижимости.
        low[u.id] = std::min(low[u.id], discoveryTime[v.id]);
      }
    }
  }
};

}  // namespace graph

#endif  // BRIDGES_AND_ARTICULATION_POINTS_H