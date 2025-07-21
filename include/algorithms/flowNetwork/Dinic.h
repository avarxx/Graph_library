#ifndef DINIC_H
#define DINIC_H

#include <climits>
#include <queue>
#include <unordered_map>

#include "FlowNetwork.h"

namespace graph {

/**
 * @class DinicSolver
 * @brief Класс для решения задачи нахождения максимального потока в сети с
 * использованием алгоритма Диница.
 *
 * Этот класс реализует алгоритм Диница для нахождения максимального потока в
 * сети. Алгоритм использует построение слоистых сетей и поиск блокирующего
 * потока.
 */
template <typename GraphType>
class DinicSolver {
 public:
  /**
   * @brief Конструктор класса DinicSolver.
   *
   * @param network Сеть, для которой будет вычисляться максимальный поток.
   */
  explicit DinicSolver(FlowNetwork<GraphType>& network) : network(network) {}

  /**
   * @brief Вычисляет максимальный поток в сети.
   *
   * @param source Исток (начальная вершина).
   * @param sink Сток (конечная вершина).
   * @return Значение максимального потока.
   */
  int computeMaxFlow(const Vertex& source, const Vertex& sink) {
    this->source = source;
    this->sink = sink;

    int maxFlow = 0;
    while (buildLevelGraph(source, sink)) {
      initializePtr();
      while (int flow = findBlockingFlow(source, sink)) {
        maxFlow += flow;
      }
    }
    return maxFlow;
  }

 private:
  FlowNetwork<GraphType>& network;  ///< Сеть, для которой вычисляется поток.
  std::unordered_map<Vertex, int> level;  ///< Уровни вершин в слоистой сети.
  std::unordered_map<Vertex, size_t>
      ptr;  ///< Указатели для поиска блокирующего потока.
  Vertex source;  ///< Исток (начальная вершина).
  Vertex sink;    ///< Сток (конечная вершина).

  /**
   * @brief Строит слоистую сеть.
   *
   * @param source Исток (начальная вершина).
   * @param sink Сток (конечная вершина).
   * @return true, если сток достижим из истока, иначе false.
   */
  bool buildLevelGraph(const Vertex& source, const Vertex& sink) {
    level.clear();
    std::queue<Vertex> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty()) {
      auto u = q.front();
      q.pop();

      for (const auto& e : network.getAdjacent(u)) {
        if (!level.count(e.target) && e.flow < e.capacity) {
          level[e.target] = level[u] + 1;
          q.push(e.target);
        }
      }
    }
    return level.count(sink);
  }

  /**
   * @brief Инициализирует указатели для поиска блокирующего потока.
   */
  void initializePtr() {
    ptr.clear();
    for (const auto& [v, _] : network.getAdjacentMut(source)) {
      ptr[v] = 0;
    }
  }

  /**
   * @brief Находит блокирующий поток в слоистой сети.
   *
   * @param u Текущая вершина.
   * @param sink Сток (конечная вершина).
   * @param minCap Минимальная пропускная способность на пути.
   * @return Значение найденного потока.
   */
  int findBlockingFlow(const Vertex& u, const Vertex& sink,
                       int minCap = INT_MAX) {
    if (u == sink) return minCap;
    for (size_t& i = ptr[u]; i < network.getAdjacentMut(u).size(); ++i) {
      auto& e = network.getAdjacentMut(u)[i];
      if (level[e.target] == level[u] + 1 && e.flow < e.capacity) {
        int flow = findBlockingFlow(e.target, sink,
                                    std::min(minCap, e.capacity - e.flow));
        if (flow > 0) {
          e.flow += flow;
          e.reverse->flow -= flow;
          return flow;
        }
      }
    }
    return 0;
  }
};

}  // namespace graph

#endif  // DINIC_H