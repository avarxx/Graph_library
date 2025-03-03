#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <functional>
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
  explicit Vertex(int id) : id(id){};

  /**
   * @brief Конструктор по умолчанию.
   */
  Vertex() : id(0){};
};

/**
 * @brief Оператор сравнения вершин.
 * @param left Левая вершина для сравнения.
 * @param right Правая вершина для сравнения.
 * @return true, если идентификаторы вершин равны, иначе false.
 */
inline bool operator==(const Vertex& left, const Vertex& right) {
  return left.id == right.id;
}

// bool operator!=(const Vertex& left, const Vertex& right) {
//   return !(left == right);
// }
/**
 * @brief Класс, представляющий ребро графа.
 */
class Edge {
 public:
  Vertex source;  ///< Идентификатор исходной вершины.
  Vertex target;  ///< Идентификатор целевой вершины.
  int capacity;  ///< Пропускная способность ребра (для алгоритмов потока)
  int flow;  ///< Текущий поток через ребро (для алгоритмов потока)

  /**
   * @brief Конструктор ребра с параметром пропускной способности.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   * @param capacity Пропускная способность ребра (по умолчанию 0).
   */
  Edge(const Vertex& source, const Vertex& target, int capacity = 0)
      : source(source), target(target), capacity(capacity), flow(0){};

  /**
   * @brief Конструктор по умолчанию.
   */
  Edge() : source(0), target(0), capacity(0), flow(0){};

  /**
   * @brief Оператор присваивания.
   * @param right Ребро, из которого копируются данные.
   * @return Ссылка на текущее ребро.
   */
  Edge& operator=(const Edge& right) {
    if (this == &right) {
      return *this;
    }
    this->source = right.source;
    this->target = right.target;
    this->capacity = right.capacity;
    this->flow = right.flow;
    return *this;
  }

  /**
   * @brief Вычисляет остаточную пропускную способность.
   * @return Разница между пропускной способностью и текущим потоком.
   */
  int residual() const { return capacity - flow; }
};

/**
 * @brief Оператор сравнения рёбер.
 * @param left Левое ребро для сравнения.
 * @param right Правое ребро для сравнения.
 * @return true, если исходные и целевые вершины рёбер равны, иначе false.
 */
inline bool operator==(const Edge& left, const Edge& right) {
  return left.source == right.source && left.target == right.target;
}

/**
 * @brief Класс, представляющий взвешенное ребро графа.
 * @tparam WeightType Тип веса ребра.
 */
template <typename WeightType>
class WeightedEdge : public Edge {
 public:
  WeightType weight;  ///< Вес ребра.

  /**
   * @brief Конструктор взвешенного ребра с параметром пропускной способности.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   * @param weight Вес ребра (по умолчанию 0).
   * @param capacity Пропускная способность (по умолчанию 0).
   */
  WeightedEdge(const Vertex& source, const Vertex& target,
               WeightType weight = 0, int capacity = 0)
      : Edge(source, target, capacity), weight(weight){};

  /**
   * @brief Конструктор взвешенного ребра с весом по умолчанию.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   */
  WeightedEdge(const Vertex& source, const Vertex& target)
      : Edge(source, target, 0), weight(0){};
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
   * @param vertex Вершина для добавления.
   */
  virtual void addVertex(const VertexType& vertex);

  /**
   * @brief Удаляет вершину из графа.
   * @param vertex Вершина для удаления.
   */
  virtual void removeVertex(const VertexType& vertex);

  /**
   * @brief Добавляет ребро с указанием пропускной способности.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   * @param capacity Пропускная способность ребра (по умолчанию 0).
   */
  virtual void addEdge(const VertexType& source, const VertexType& target,
                       int capacity = 0);

  /**
   * @brief Удаляет ребро из графа.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   */
  virtual void removeEdge(const VertexType& source, const VertexType& target);

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
  virtual typename std::vector<VertexType>::iterator getNeighborsIterator(
      const VertexType& vertexId);

  /**
   * @brief Возвращает итератор с фильтром по соседям вершины.
   * @param vertexId Идентификатор вершины.
   * @param filter Функция-фильтр.
   * @return Итератор по соседям вершины, удовлетворяющим фильтру.
   */
  virtual typename std::vector<VertexType>::iterator
  getFilteredNeighborsIterator(const VertexType& vertexId,
                               bool (*filter)(VertexType));

  /**
   * @brief Проверяет наличие вершины в графе.
   * @param id Идентификатор вершины.
   * @return true, если вершина существует, иначе false.
   */
  virtual bool hasVertex(const VertexType& id) const;

  /**
   * @brief Проверяет наличие ребра в графе.
   * @param source Идентификатор исходной вершины.
   * @param target Идентификатор целевой вершины.
   * @return true, если ребро существует, иначе false.
   */
  virtual bool hasEdge(const VertexType& source,
                       const VertexType& target) const;

  /**
   * @brief Возвращает список смежных вершин.
   * @param vertex Вершина, для которой ищутся смежные вершины.
   * @return Вектор смежных вершин.
   */
  virtual std::vector<VertexType> getAdjacencyVertices(
      const VertexType& vertex);
};

}  // namespace graph

namespace std {
/**
 * @brief Специализация хэш-функции для класса Vertex.
 */
template <>
struct hash<graph::Vertex> {
  /**
   * @brief Оператор вычисления хэша.
   * @param v Вершина, для которой вычисляется хэш.
   * @return Хэш-значение вершины.
   */
  std::size_t operator()(const graph::Vertex& v) const noexcept {
    return std::hash<int>{}(v.id);
  }
};
}  // namespace std

#endif  // GRAPH_H