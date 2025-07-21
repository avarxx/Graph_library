#ifndef BFS_VISITOR_H
#define BFS_VISITOR_H

#include <iostream>

namespace graph {

/**
 * @brief Базовый класс для посетителя (Visitor) в алгоритме BFS.
 * @tparam VertexType Тип вершины.
 * @tparam EdgeType Тип ребра.
 */
template <typename VertexType, typename EdgeType>
class Visitor {
 public:
  /**
   * @brief Виртуальный деструктор.
   */
  virtual ~Visitor() = default;

  /**
   * @brief Метод, вызываемый при обнаружении вершины.
   * @param vertex Вершина, которая была обнаружена.
   */
  virtual void discoverVertex(const VertexType& vertex) {}

  /**
   * @brief Метод, вызываемый при посещении вершины.
   * @param vertex Вершина, которая была посещена.
   */
  virtual void visitVertex(const VertexType& vertex) {}

  /**
   * @brief Метод, вызываемый при исследовании ребра.
   * @param edge Ребро, которое было исследовано.
   */
  virtual void examineEdge(const EdgeType& edge) {}

  /**
   * @brief Метод, вызываемый при добавлении ребра в дерево поиска.
   * @param edge Ребро, добавленное в дерево поиска.
   */
  virtual void treeEdge(const EdgeType& edge) {}

  /**
   * @brief Метод, вызываемый при завершении обработки вершины.
   * @param vertex Вершина, обработка которой завершена.
   */
  virtual void finishVertex(const VertexType& vertex) {}
};

/**
 * @brief Реализация посетителя по умолчанию для алгоритма BFS.
 * @tparam VertexType Тип вершины.
 * @tparam EdgeType Тип ребра.
 */
template <typename VertexType, typename EdgeType>
class DefaultVisitor : public Visitor<VertexType, EdgeType> {
 public:
  /**
   * @brief Деструктор по умолчанию.
   */
  ~DefaultVisitor() = default;

  /**
   * @brief Метод, вызываемый при обнаружении вершины.
   * @param vertex Вершина, которая была обнаружена.
   */
  void discoverVertex(const VertexType& vertex) override {
    std::cout << "discovering vertex " << vertex.id << '\n';
  }

  /**
   * @brief Метод, вызываемый при посещении вершины.
   * @param vertex Вершина, которая была посещена.
   */
  void visitVertex(const VertexType& vertex) override {
    std::cout << "visiting vertex " << vertex.id << '\n';
  }

  /**
   * @brief Метод, вызываемый при исследовании ребра.
   * @param edge Ребро, которое было исследовано.
   */
  void examineEdge(const EdgeType& edge) override {
    std::cout << "discovered edge " << edge.source.id << ' ' << edge.target.id
              << '\n';
  }

  /**
   * @brief Метод, вызываемый при добавлении ребра в дерево поиска.
   * @param edge Ребро, добавленное в дерево поиска.
   */
  void treeEdge(const EdgeType& edge) override {
    std::cout << "becoming a member of edges " << edge.source.id << ' '
              << edge.target.id << '\n';
  }

  /**
   * @brief Метод, вызываемый при завершении обработки вершины.
   * @param vertex Вершина, обработка которой завершена.
   */
  void finishVertex(const VertexType& vertex) override {
    std::cout << "finishing vertex " << vertex.id << '\n';
  }
};

}  // namespace graph

#endif  // BFS_VISITOR_H