#ifndef EDGE_LIST_GRAPH_H
#define EDGE_LIST_GRAPH_H

#include <unordered_set>
#include <vector>

#include "Graph.h"

namespace graph {
template <typename VernexType = Vertex, typename EdgeType = Edge>
class EdgeListGraph : public Graph<VernexType, EdgeType> 
{
  private:
    std::unordered_set<int> verticesSes;
  public:
  EdgeListGraph()  = default;

  void addVertex(int id) override;

  void removeVertex(int id) override;

  void addEdge(int source, int target) override;

  void removeEdge(int source, int target) override;

  std::vector<int>::iterator getNeighborsIterator(int vertexId) override;

  std::vector<int>::iterator getFilteredNeighborsIterator(int VertexId, bool (*filter)(int)) override;

  bool hasVertex(int id) const override;

  bool hasEdge(int source, int target) const override;

};
}  // namespace graph


// namespace graph {

// /**
//  * @brief Класс графа, реализованный на основе списка рёбер.
//  * @tparam VertexType Тип вершины (по умолчанию Vertex).
//  * @tparam EdgeType Тип ребра (по умолчанию Edge).
//  */
// template <typename VertexType = Vertex, typename EdgeType = Edge>
// class EdgeListGraph : public Graph<VertexType, EdgeType> {
//  private:
//   std::unordered_set<int> verticesSet;  // Множество вершин для быстрого
//   поиска

//  public:
//   /**
//    * @brief Конструктор по умолчанию.
//    */
//   EdgeListGraph() = default;

//   /**
//    * @brief Добавляет вершину в граф.
//    * @param id Уникальный идентификатор вершины.
//    */
//   void addVertex(int id) override;

//   /**
//    * @brief Удаляет вершину из графа.
//    * @param id Уникальный идентификатор вершины.
//    */
//   void removeVertex(int id) override;

//   /**
//    * @brief Добавляет ребро в граф.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    */
//   void addEdge(int source, int target) override;

//   /**
//    * @brief Удаляет ребро из графа.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    */
//   void removeEdge(int source, int target) override;

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

//   /**
//    * @brief Проверяет наличие вершины в графе.
//    * @param id Идентификатор вершины.
//    * @return true, если вершина существует, иначе false.
//    */
//   bool hasVertex(int id) const override;

//   /**
//    * @brief Проверяет наличие ребра в графе.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    * @return true, если ребро существует, иначе false.
//    */
//   bool hasEdge(int source, int target) const override;
// };

// }  // namespace graph

#endif  // EDGE_LIST_GRAPH_H