#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <stack>
#include <unordered_set>

#include "../bfs_dfs/DFS.h"
#include "FlowNetwork.h"

namespace graph {

/**
 * @class FordFulkerson
 * @brief Класс для решения задачи нахождения максимального потока в сети с
 * использованием алгоритма Форда-Фалкерсона.
 *
 * Этот класс реализует алгоритм Форда-Фалкерсона, который использует поиск в
 * глубину (DFS) для нахождения увеличивающих путей в остаточной сети.
 */
template <typename GraphType>
class FordFulkerson {
 public:
  /**
   * @brief Конструктор класса FordFulkerson.
   *
   * @param network Сеть потоков, для которой будет вычисляться максимальный
   * поток.
   */
  explicit FordFulkerson(FlowNetwork<GraphType>& network) : network(network) {}

  /**
   * @brief Вычисляет максимальный поток в сети.
   *
   * @param source Исток (начальная вершина).
   * @param sink Сток (конечная вершина).
   * @return Значение максимального потока.
   */
  int computeMaxFlow(const Vertex& source, const Vertex& sink) {
    int max_flow = 0;

    while (true) {
      // Используем DFS для поиска увеличивающего пути
      std::unordered_set<Vertex> visited;
      int path_flow = findAugmentingPath(source, sink, visited);

      // Если увеличивающий путь не найден, завершаем алгоритм
      if (path_flow == 0) break;

      max_flow += path_flow;
    }

    return max_flow;
  }

 private:
  FlowNetwork<GraphType>&
      network;  ///< Сеть потоков, для которой вычисляется максимальный поток.

  /**
   * @brief Поиск увеличивающего пути с использованием DFS.
   *
   * @param u Текущая вершина.
   * @param sink Сток (конечная вершина).
   * @param visited Множество посещенных вершин.
   * @return Поток, который можно пропустить по найденному пути.
   */
  int findAugmentingPath(Vertex& u, Vertex& sink,
                         std::unordered_set<Vertex>& visited) {
    struct FlowVisitor
        : public Visitor<Vertex, typename FlowNetwork<GraphType>::FlowEdge> {
      std::unordered_map<Vertex, Vertex>& parent;
      int& path_flow;

      FlowVisitor(std::unordered_map<Vertex, Vertex>& p, int& pf)
          : parent(p), path_flow(pf) {}

      void treeEdge(
          const typename FlowNetwork<GraphType>::FlowEdge& e) override {
        parent[e.target] = e.source;
        path_flow = std::min(path_flow, e.residual());
      }
    };

    std::unordered_map<Vertex, Vertex> parent;
    int path_flow = std::numeric_limits<int>::max();

    FlowVisitor visitor(parent, path_flow);
    DFS<Vertex, typename FlowNetwork<GraphType>::FlowEdge>(network, u, visitor);

    // Если сток не был достигнут, возвращаем 0
    if (parent.find(sink) == parent.end()) return 0;

    // Обновляем потоки вдоль найденного пути
    for (Vertex v = sink; v != u; v = parent[v]) {
      Vertex& u_parent = parent[v];
      for (auto& e : network.getAdjacentMut(u_parent)) {
        if (e.target == v) {
          e.flow += path_flow;
          e.reverse->flow -= path_flow;
          break;
        }
      }
    }

    return path_flow;
  }
};

}  // namespace graph

#endif  // FORD_FULKERSON_H