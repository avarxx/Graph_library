#ifndef EDMONDS_KARP_H
#define EDMONDS_KARP_H

#include <limits>
#include <queue>
#include <unordered_map>

#include "FlowNetwork.h"
#include "../../graph/Graph.h"
#include "../bfs_dfs/BFS.h"

namespace graph {

/**
 * @class EdmondsKarp
 * @brief Класс для решения задачи нахождения максимального потока в сети с
 * использованием алгоритма Эдмондса-Карпа.
 *
 * Этот класс реализует алгоритм Эдмондса-Карпа, который является реализацией
 * метода Форда-Фалкерсона с использованием BFS для поиска увеличивающих путей в
 * остаточной сети.
 */
template <typename GraphType>
class EdmondsKarp {
 private:
  // Теперь напрямую указываем, что работаем с FlowNetwork
  FlowNetwork<GraphType>& network;

  // Явно указываем, что используем типы Vertex и Edge
  std::unordered_map<Vertex, Vertex>
      parent;  ///< Хранение родительских вершин для восстановления пути.

  /**
   * @brief Модифицированный BFS для поиска кратчайшего пути в остаточной сети.
   *
   * @param source Исток (начальная вершина).
   * @param sink Сток (конечная вершина).
   * @return true, если путь от истока к стоку существует, иначе false.
   */
  bool bfs(const Vertex& source, const Vertex& sink) {
    struct FlowVisitor : public Visitor<Vertex, Edge> {
      std::unordered_map<Vertex, Vertex>&
          parent;  ///< Ссылка на родительские вершины.

      /**
       * @brief Конструктор для FlowVisitor.
       *
       * @param p Ссылка на родительские вершины.
       */
      FlowVisitor(std::unordered_map<Vertex, Vertex>& p) : parent(p) {}

      /**
       * @brief Обработка ребра дерева в BFS.
       *
       * @param e Ребро, которое обрабатывается.
       */
      void treeEdge(const Edge& e) override { parent[e.target] = e.source; }
    };

    parent.clear();
    FlowVisitor visitor(parent);

    // Используем базовый граф из сети потоков
    GraphType& graph = network.getBaseGraph();
    std::vector<int> distances = BFS<Vertex, Edge>(graph, source, visitor);

    return parent.find(sink) != parent.end();
  }

 public:
  /**
   * @brief Конструктор класса EdmondsKarp.
   *
   * @param network Сеть потоков, для которой будет вычисляться максимальный
   * поток.
   */
  EdmondsKarp(FlowNetwork<GraphType>& network) : network(network) {}

  /**
   * @brief Вычисляет максимальный поток в сети.
   *
   * @param source Исток (начальная вершина).
   * @param sink Сток (конечная вершина).
   * @return Значение максимального потока.
   */
  int computeMaxFlow(const Vertex& source, const Vertex& sink) {
    int max_flow = 0;

    // Получаем базовый граф из сети потоков
    GraphType& graph = network.getBaseGraph();

    while (bfs(source, sink)) {
      // Находим минимальную остаточную пропускную способность
      int path_flow = std::numeric_limits<int>::max();

      // Проход от стока к истоку
      for (Vertex v = sink; v != source; v = parent[v]) {
        Vertex vp(parent[v], v);
        if (network.hasResidualCapacity(vp)) {
          path_flow = std::min(path_flow, network.getResidualCapacity(vp));
        }
      }

      // Обновляем потоки
      for (Vertex v = sink; v != source; v = parent[v]) {
        Vertex vp(parent[v], v);
        network.addFlow(vp, path_flow);
      }

      max_flow += path_flow;
    }
    return max_flow;
  }
};

}  // namespace graph

#endif  // EDMONDS_KARP_H