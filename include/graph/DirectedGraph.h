#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "Graph.h"

namespace graph {

template <typename VertexType = Vertex, typename EdgeType = Edge>
class DirectedGraph : public Graph<VertexType, EdgeType> {
 public:
  DirectedGraph() = default;
  void addEdge(int source, int target) override;
  void removeEdge(int source, int target) override;
  bool hasEdge(int source, int target) const override;
  std::vector<int>::iterator getNeighborsIterator(int vertexId) override;
  std::vector<int>::iterator getFilteredNeighborsIterator(
      int vertexId, bool (*filter)(int)) override;
};
}  // namespace graph

// namespace graph {

// /**
//  * @brief Класс ориентированного графа.
//  * @tparam VertexType Тип вершины (по умолчанию Vertex).
//  * @tparam EdgeType Тип ребра (по умолчанию Edge).
//  */
// template <typename VertexType = Vertex, typename EdgeType = Edge>
// class DirectedGraph : public Graph<VertexType, EdgeType> {
//  public:
//   /**
//    * @brief Конструктор по умолчанию.
//    */
//   DirectedGraph() = default;

//   /**
//    * @brief Добавляет ориентированное ребро в граф.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    */
//   void addEdge(int source, int target) override;

//   /**
//    * @brief Удаляет ориентированное ребро из графа.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    */
//   void removeEdge(int source, int target) override;

//   /**
//    * @brief Проверяет наличие ориентированного ребра в графе.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    * @return true, если ребро существует, иначе false.
//    */
//   bool hasEdge(int source, int target) const override;

//   /**
//    * @brief Возвращает итератор по соседям вершины (только исходящие рёбра).
//    * @param vertexId Идентификатор вершины.
//    * @return Итератор по соседям вершины.
//    */
//   std::vector<int>::iterator getNeighborsIterator(int vertexId) override;

//   /**
//    * @brief Возвращает итератор с фильтром по соседям вершины (только
//    исходящие рёбра).
//    * @param vertexId Идентификатор вершины.
//    * @param filter Функция-фильтр.
//    * @return Итератор по соседям вершины, удовлетворяющим фильтру.
//    */
//   std::vector<int>::iterator getFilteredNeighborsIterator(
//       int vertexId, bool (*filter)(int)) override;
// };

// }  // namespace graph

#endif  // DIRECTED_GRAPH_H