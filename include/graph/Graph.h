#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

namespace graph {

/**
 * @brief Класс, представляющий вершину графа.
 */
class Vertex {
 public:
  int id;  ///< Уникальный идентификатор вершины.

  /**
   * @brief Конструктор вершины.
   * @param id Уникальный идентификатор вершины.
   */
  explicit Vertex(int id) : id(id) {}
  // explicit не дает компилятору делать неявные преобразования 
};

/**
 * @brief Класс, представляющий ребро графа.
 */
class Edge {
 public:
  int source;  ///< Идентификатор исходной вершины.
  int target;  ///< Идентификатор целевой вершины.

  /**
   * @brief Конструктор ребра.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   */
  Edge(int source, int target) : source(source), target(target) {}
};

/**
 * @brief Базовый класс графа.
 * @tparam VertexType Тип вершины (по умолчанию Vertex).
 * @tparam EdgeType Тип ребра (по умолчанию Edge).
 */
template <typename VertexType = Vertex, typename EdgeType = Edge>
class Graph {
 protected:
  std::vector<VertexType> vertices;  ///< Список вершин.
  std::vector<EdgeType> edges;       ///< Список рёбер.

 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  Graph() = default;

  /**
   * @brief Виртуальный деструктор.
   */
  virtual ~Graph() = default;

  /**
   * @brief Добавляет вершину в граф.
   * @param id Уникальный идентификатор вершины.
   */
  virtual void addVertex(int id);

  /**
   * @brief Удаляет вершину из графа.
   * @param id Уникальный идентификатор вершины.
   */
  virtual void removeVertex(int id);

  /**
   * @brief Добавляет ребро в граф.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   */
  virtual void addEdge(int source, int target);

  /**
   * @brief Удаляет ребро из графа.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   */
  virtual void removeEdge(int source, int target);

  /**
   * @brief Возвращает список вершин.
   * @return Константная ссылка на список вершин.
   */
  const std::vector<VertexType>& getVertices() const;

  /**
   * @brief Возвращает список рёбер.
   * @return Константная ссылка на список рёбер.
   */
  const std::vector<EdgeType>& getEdges() const;

  /**
   * @brief Возвращает итератор по соседям вершины.
   * @param vertexId Идентификатор вершины.
   * @return Итератор по соседям вершины.
   */
  virtual std::vector<int>::iterator getNeighborsIterator(int vertexId);

  /**
   * @brief Возвращает итератор с фильтром по соседям вершины.
   * @param vertexId Идентификатор вершины.
   * @param filter Функция-фильтр.
   * @return Итератор по соседям вершины, удовлетворяющим фильтру.
   */
  virtual std::vector<int>::iterator getFilteredNeighborsIterator(
      int vertexId, bool (*filter)(int));

  /**
   * @brief Проверяет наличие вершины в графе.
   * @param id Идентификатор вершины.
   * @return true, если вершина существует, иначе false.
   */
  virtual bool hasVertex(int id) const;

  /**
   * @brief Проверяет наличие ребра в графе.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   * @return true, если ребро существует, иначе false.
   */
  virtual bool hasEdge(int source, int target) const;
};

}  // namespace graph

#endif  // GRAPH_H