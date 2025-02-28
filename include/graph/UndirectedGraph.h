#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include "Graph.h"

namespace graph {

template <typename VertexType = Vertex, typename EdgeType = Edge>
class UndirectedGraph : public Graph<VertexType, EdgeType> {
 public:
  UndirectedGraph() = default;
  void addEdge(const Vertex& source, const Vertex& target) override;
  void removeEdge(const Vertex& source, const Vertex& target) override;
  bool hasEdge(const Vertex& source, const Vertex& target) const override;
  typename std::vector<Vertex>::iterator getNeighborsIterator(const Vertex& vertexId) override;
  typename std::vector<Vertex>::iterator getFilteredNeighborsIterator(
    const Vertex& vertexId, bool (*filter)(Vertex)) override;
};

}  // namespace graph

// namespace graph {

// /**
//  * @brief Класс неориентированного графа.
//  * @tparam VertexType Тип вершины (по умолчанию Vertex).
//  * @tparam EdgeType Тип ребра (по умолчанию Edge).
//  */
// template <typename VertexType = Vertex, typename EdgeType = Edge>
// class UndirectedGraph : public Graph<VertexType, EdgeType> {
//  public:
//   /**
//    * @brief Конструктор по умолчанию.
//    */
//   UndirectedGraph() = default;

//   /**
//    * @brief Добавляет неориентированное ребро в граф.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    */
//   void addEdge(int source, int target) override;

//   /**
//    * @brief Удаляет неориентированное ребро из графа.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    */
//   void removeEdge(int source, int target) override;

//   /**
//    * @brief Проверяет наличие неориентированного ребра в графе.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    * @return true, если ребро существует, иначе false.
//    */
//   bool hasEdge(int source, int target) const override;

//   /**
//    * @brief Возвращает итератор по соседям вершины.
//    * @param vertexId Идентификатор вершины.
//    * @return Итератор по соседям вершины.
//    */
//   std::vector<int>::iterator getNeighborsIterator(int vertexId) override;

//   /**
//    * @brief Возвращает итератор с фильтром по соседям вершины.
//    * @param vertexId Идентификатор вершины.
//    * @param filter Функция-фильтр.
//    * @return Итератор по соседям вершины, удовлетворяющим фильтру.
//    */
//   std::vector<int>::iterator getFilteredNeighborsIterator(
//       int vertexId, bool (*filter)(int)) override;
// };

// }  // namespace graph

#endif  // UNDIRECTED_GRAPH_H