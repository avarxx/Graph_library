#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include <unordered_map>
#include <vector>

#include "Graph.h"

namespace graph {

/**
 * @brief Класс, реализующий граф на основе матрицы смежности.
 * @tparam VertexType Тип вершины (по умолчанию Vertex).
 * @tparam EdgeType Тип ребра (по умолчанию Edge).
 */
template <typename VertexType = Vertex, typename EdgeType = Edge>
class AdjacencyMatrixGraph : public Graph<VertexType, EdgeType> {
 private:
  std::vector<std::vector<bool>> adjacencyMatrix;  ///< Матрица смежности.
  std::unordered_map<VertexType, size_t>
      vertexToIndex;  ///< Соответствие ID вершины и индекса в матрице.
  std::unordered_map<size_t, VertexType>
      indexToVertex;  ///< Соответствие индекса в матрице и ID вершины.

  /**
   * @brief Возвращает индекс вершины в матрице смежности.
   * @param id Идентификатор вершины.
   * @return Индекс вершины в матрице смежности.
   */
  size_t getVertexIndex(const VertexType& id) const;

 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  AdjacencyMatrixGraph() = default;

  /**
   * @brief Добавляет вершину в граф.
   * @param id Вершина для добавления.
   */
  void addVertex(const VertexType& id) override;

  /**
   * @brief Удаляет вершину из графа.
   * @param id Вершина для удаления.
   */
  void removeVertex(const VertexType& id) override;

  /**
   * @brief Добавляет ребро в граф.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   */
  void addEdge(const VertexType& source, const VertexType& target, int capacity = 0) override;

  /**
   * @brief Удаляет ребро из графа.
   * @param source Исходная вершина ребра.
   * @param target Целевая вершина ребра.
   */
  void removeEdge(const VertexType& source, const VertexType& target) override;

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

  /**
   * @brief Возвращает список смежных вершин.
   * @param vertex Вершина, для которой ищутся смежные вершины.
   * @return Вектор смежных вершин.
   */
  std::vector<VertexType> getAdjacencyVertices(
      const VertexType& vertex) override;
};

}  // namespace graph

#endif  // ADJACENCY_MATRIX_GRAPH_H