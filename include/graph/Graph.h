#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>
#include <functional>

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
  explicit Vertex(int id) : id(id) {};
  // explicit не дает компилятору делать неявные преобразования 

  Vertex() : id(0) {};
};

inline bool operator==(const Vertex& left, const Vertex& right) {
  return left.id == right.id;
}

/**
 * @brief Класс, представляющий ребро графа.
 */
class Edge {
 public:
  Vertex source;  ///< Идентификатор исходной вершины.
  Vertex target;  ///< Идентификатор целевой вершины.

  /**
   * @brief Конструктор ребра.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   */
  Edge(const Vertex& source, const Vertex& target) : source(source), target(target) {};
  Edge() : source(0), target(0) {};
  Edge& operator=(const Edge& right) {
    if (this == &right) {
      return *this;
    }
    this->source = right.source;
    this->target = right.target;
    return *this;
  }
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
  virtual void addVertex(const Vertex& vertex);

  /**
   * @brief Удаляет вершину из графа.
   * @param id Уникальный идентификатор вершины.
   */
  virtual void removeVertex(const Vertex& vertex);

  /**
   * @brief Добавляет ребро в граф.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   */
  virtual void addEdge(const Vertex& source, const Vertex& target);

  /**
   * @brief Удаляет ребро из графа.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   */
  virtual void removeEdge(const Vertex& source, const Vertex& target);

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
  virtual typename std::vector<VertexType>::iterator getNeighborsIterator(const Vertex& vertexId);

  /**
   * @brief Возвращает итератор с фильтром по соседям вершины.
   * @param vertexId Идентификатор вершины.
   * @param filter Функция-фильтр.
   * @return Итератор по соседям вершины, удовлетворяющим фильтру.
   */
  virtual typename std::vector<VertexType>::iterator getFilteredNeighborsIterator(
      const Vertex& vertexId, bool (*filter)(Vertex));

  /**
   * @brief Проверяет наличие вершины в графе.
   * @param id Идентификатор вершины.
   * @return true, если вершина существует, иначе false.
   */
  virtual bool hasVertex(const Vertex& id) const;

  /**
   * @brief Проверяет наличие ребра в графе.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   * @return true, если ребро существует, иначе false.
   */
  virtual bool hasEdge(const Vertex& source, const Vertex& target) const;
};

}  // namespace graph

namespace std {
  template <>
  struct hash<graph::Vertex> {
      std::size_t operator()(const graph::Vertex& v) const noexcept {
          return std::hash<int>{}(v.id);
      }
  };
}

#endif  // GRAPH_H