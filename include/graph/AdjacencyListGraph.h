#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H


#include "Graph.h"
#include <unordered_map>


namespace graph
{
  template<typename VertexType = Vertex, typename EdgeType = Edge>
  class AdjacencyListGraph : public Graph<Vertex, Edge>
  {
  public:
    std::unordered_map<Vertex, std::vector<Vertex>> adjacencyList;
  public:
    AdjacencyListGraph() : Graph<Vertex, Edge>() {};
    ~AdjacencyListGraph() = default;

    void addVertex(const Vertex& id) override;

    void removeVertex(const Vertex& id) override;

    void addEdge(const Vertex& source, const Vertex& target) override; 

    void removeEdge(const Vertex& source, const Vertex& target) override;

    typename std::vector<VertexType>::iterator getNeighborsIterator(const Vertex& vertexid) override;
    
    typename std::vector<VertexType>::iterator getFilteredNeighborsIterator(const Vertex& vertexid, bool (*filter)(Vertex)) override;
    
    const std::unordered_map<Vertex, std::vector<Vertex>>& getAdjacencyList() const;

    bool hasVertex(const Vertex& id) const override;

    bool hasEdge(const Vertex& source, const Vertex& target) const override;
  };
  
} //namespace graph


#endif // ADJACENCY_LIST_GRAPH_H


// версия с дксигеном ее невозможно читать, ноль читабельности кода

// namespace graph {

// /**
//  * @brief Класс графа, реализованный на основе списка смежности.
//  * @tparam VertexType Тип вершины (по умолчанию Vertex).
//  * @tparam EdgeType Тип ребра (по умолчанию Edge).
//  */
// template <typename VertexType = Vertex, typename EdgeType = Edge>
// class AdjacencyListGraph : public Graph<VertexType, EdgeType> {
//  private:
//   // Список смежности: ключ — ID вершины, значение — список смежных вершин
//   std::unordered_map<int, std::vector<int>> adjacencyList;

//  public:
//   /**
//    * @brief Конструктор по умолчанию.
//    */
//   AdjacencyListGraph() = default;

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
//    * @brief Возвращает список смежности.
//    * @return Константная ссылка на список смежности.
//    */
//   const std::unordered_map<int, std::vector<int>>& getAdjacencyList() const;

  // /**
  //  * @brief Проверяет наличие вершины в графе.
  //  * @param id Идентификатор вершины.
  //  * @return true, если вершина существует, иначе false.
  //  */
//     bool hasVertex(int id) const override;

  // /**
  //  * @brief Проверяет наличие ребра в графе.
  //  * @param source Идентификатор исходной вершины.
  //  * @param target Идентификатор целевой вершины.
  //  * @return true, если ребро существует, иначе false.
  //  */
//     bool hasEdge(int source, int target) const override;
// };


// }  // namespace graph
