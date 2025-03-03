#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include "Graph.h"

namespace graph {

/**
 * @brief Класс, реализующий взвешенный граф.
 * @tparam VertexType Тип вершины (по умолчанию Vertex).
 * @tparam WeightType Тип веса ребра (по умолчанию int).
 */
template <typename VertexType = Vertex, typename WeightType = int>
class WeightedGraph : public Graph<VertexType, WeightedEdge<WeightType>> {
 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  WeightedGraph() = default;

  /**
   * @brief Добавляет взвешенное ребро в граф.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   * @param weight Вес ребра.
   */
  void addEdge(const VertexType& source, const VertexType& target,
               WeightType weight);

  /**
   * @brief Добавляет ребро в граф с весом по умолчанию.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   */
  // void addEdge(const VertexType& source, const VertexType& target, int capacity = 0) override;

  /**
   * @brief Возвращает вес ребра.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   * @return Вес ребра.
   */
  WeightType getEdgeWeight(const VertexType& source,
                           const VertexType& target) const;

  /**
   * @brief Устанавливает вес ребра.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   * @param weight Новый вес ребра.
   */
  void setEdgeWeight(const VertexType& source, const VertexType& target,
                     WeightType weight);

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
      const VertexType& vertex)  override;

  /**
   * @brief Добавляет вершину в граф.
   * @param vertex Вершина для добавления.
   */
  void addVertex(const VertexType& vertex) override;

  /**
   * @brief Удаляет вершину из графа.
   * @param vertex Вершина для удаления.
   */
  void removeVertex(const VertexType& vertex) override;

  /**
   * @brief Удаляет ребро из графа.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   */
  void removeEdge(const VertexType& source, const VertexType& target);

  /**
   * @brief Проверяет наличие вершины в графе.
   * @param id Идентификатор вершины.
   * @return true, если вершина существует, иначе false.
   */
  bool hasVertex(const VertexType& id) const override;

  /**
   * @brief Проверяет наличие ребра в графе.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   * @return true, если ребро существует, иначе false.
   */
  bool hasEdge(const VertexType& source,
               const VertexType& target) const override;
};

}  // namespace graph

#endif  // WEIGHTED_GRAPH_H