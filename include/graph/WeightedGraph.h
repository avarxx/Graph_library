#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include "Graph.h"

namespace graph {

template <typename WeightType>
class WeightedEdge : public Edge {
 public:
  WeightType weight;
  WeightedEdge(int source, int target, WeightType weight)
      : Edge(source, target), weight(weight) {}
};

template <typename VertexType = Vertex, typename WeightType = int>
class WeightedGraph : public Graph<VertexType, WeightedEdge<WeightType>> {
 public:
  WeightedGraph() = default;
  void addEdge(int source, int target, WeightType weight);
  WeightType getEdgeWeight(int source, int target) const;
  void setEdgeWeight(int source, int target, WeightType weight);
};

}  // namespace graph

// namespace graph {

// /**
//  * @brief Класс, представляющий взвешенное ребро.
//  */
// template <typename WeightType>
// class WeightedEdge : public Edge {
//  public:
//   WeightType weight;  ///< Вес ребра.

//   /**
//    * @brief Конструктор взвешенного ребра.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    * @param weight Вес ребра.
//    */
//   WeightedEdge(int source, int target, WeightType weight)
//       : Edge(source, target), weight(weight) {}
// };

// /**
//  * @brief Класс взвешенного графа.
//  * @tparam VertexType Тип вершины (по умолчанию Vertex).
//  * @tparam WeightType Тип веса рёбер (по умолчанию int).
//  */
// template <typename VertexType = Vertex, typename WeightType = int>
// class WeightedGraph : public Graph<VertexType, WeightedEdge<WeightType>> {
//  public:
//   /**
//    * @brief Конструктор по умолчанию.
//    */
//   WeightedGraph() = default;

//   /**
//    * @brief Добавляет взвешенное ребро в граф.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    * @param weight Вес ребра.
//    */
//   void addEdge(int source, int target, WeightType weight);

//   /**
//    * @brief Возвращает вес ребра.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    * @return Вес ребра.
//    * @throws std::out_of_range Если ребро не существует.
//    */
//   WeightType getEdgeWeight(int source, int target) const;

//   /**
//    * @brief Устанавливает вес ребра.
//    * @param source Идентификатор исходной вершины.
//    * @param target Идентификатор целевой вершины.
//    * @param weight Новый вес ребра.
//    * @throws std::out_of_range Если ребро не существует.
//    */
//   void setEdgeWeight(int source, int target, WeightType weight);
// };

// }  // namespace graph

#endif  // WEIGHTED_GRAPH_H