#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include "Graph.h"

namespace graph {

/**
 * @brief Класс, реализующий неориентированный граф.
 * @tparam VertexType Тип вершины (по умолчанию Vertex).
 * @tparam EdgeType Тип ребра (по умолчанию Edge).
 */
template <typename VertexType = Vertex, typename EdgeType = Edge>
class UndirectedGraph : public Graph<VertexType, EdgeType> {
 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  UndirectedGraph() = default;

  /**
   * @brief Добавляет неориентированное ребро в граф.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   */
  void addEdge(const VertexType& source, const VertexType& target, int capacity = 0) override;

  /**
   * @brief Удаляет неориентированное ребро из графа.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   */
  void removeEdge(const VertexType& source, const VertexType& target) override;

  /**
   * @brief Проверяет наличие неориентированного ребра в графе.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   * @return true, если ребро существует, иначе false.
   */
  bool hasEdge(const VertexType& source,
               const VertexType& target) const override;

  /**
   * @brief Возвращает итератор по соседям вершины.
   * @param vertexId Идентификатор вершины.
   * @return Итератор по соседям вершины.
   */
  typename std::vector<VertexType>::iterator getNeighborsIterator(
      const VertexType& vertexId) override;

  /**
   * @brief Возвращает итератор по соседям вершины с фильтром.
   * @param vertexId Идентификатор вершины.
   * @param filter Функция-фильтр для соседей.
   * @return Итератор по соседям вершины, удовлетворяющим фильтру.
   */
  typename std::vector<VertexType>::iterator getFilteredNeighborsIterator(
      const VertexType& vertexId, bool (*filter)(VertexType)) override;

  /**
   * @brief Возвращает список смежных вершин.
   * @param vertex Вершина, для которой ищутся смежные вершины.
   * @return Вектор смежных вершин.
   */
  std::vector<VertexType> getAdjacencyVertices(
      const VertexType& vertex) override;
};

}  // namespace graph

#endif  // UNDIRECTED_GRAPH_H