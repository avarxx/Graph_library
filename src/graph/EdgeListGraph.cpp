#include "../../include/graph/EdgeListGraph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void EdgeListGraph<VertexType, EdgeType>::addVertex(int id) {
  if (!hasVertex(id)) {
    this->vertices.emplace_back(id);
    verticesSet.insert(id);
  }
}

template <typename VertexType, typename EdgeType>
void EdgeListGraph<VertexType, EdgeType>::removeVertex(int id) {
  if (hasVertex(id)) {
    // Удаляем вершину из списка вершин
    this->vertices.erase(
        std::remove_if(this->vertices.begin(), this->vertices.end(),
                       [id](const VertexType& v) { return v.id == id; }),
        this->vertices.end());

    // Удаляем вершину из множества
    verticesSet.erase(id);

    // Удаляем все рёбра, связанные с этой вершиной
    this->edges.erase(std::remove_if(this->edges.begin(), this->edges.end(),
                                     [id](const EdgeType& e) {
                                       return e.source == id || e.target == id;
                                     }),
                      this->edges.end());
  }
}

template <typename VertexType, typename EdgeType>
void EdgeListGraph<VertexType, EdgeType>::addEdge(int source, int target) {
  if (hasVertex(source) && hasVertex(target) && !hasEdge(source, target)) {
    this->edges.emplace_back(source, target);
  }
}

template <typename VertexType, typename EdgeType>
void EdgeListGraph<VertexType, EdgeType>::removeEdge(int source, int target) {
  this->edges.erase(std::remove_if(this->edges.begin(), this->edges.end(),
                                   [source, target](const EdgeType& e) {
                                     return e.source == source &&
                                            e.target == target;
                                   }),
                    this->edges.end());
}

template <typename VertexType, typename EdgeType>
std::vector<int>::iterator
EdgeListGraph<VertexType, EdgeType>::getNeighborsIterator(int vertexId) {
  static std::vector<int> neighbors;
  neighbors.clear();
  if (hasVertex(vertexId)) {
    for (const auto& edge : this->edges) {
      if (edge.source == vertexId) {
        neighbors.push_back(edge.target);
      }
    }
  }
  return neighbors.begin();
}

template <typename VertexType, typename EdgeType>
std::vector<int>::iterator
EdgeListGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
    int vertexId, bool (*filter)(int)) {
  static std::vector<int> filteredNeighbors;
  filteredNeighbors.clear();
  if (hasVertex(vertexId)) {
    for (const auto& edge : this->edges) {
      if (edge.source == vertexId && filter(edge.target)) {
        filteredNeighbors.push_back(edge.target);
      }
    }
  }
  return filteredNeighbors.begin();
}

template <typename VertexType, typename EdgeType>
bool EdgeListGraph<VertexType, EdgeType>::hasVertex(int id) const {
  return verticesSet.find(id) != verticesSet.end();
}

template <typename VertexType, typename EdgeType>
bool EdgeListGraph<VertexType, EdgeType>::hasEdge(int source,
                                                  int target) const {
  return std::any_of(this->edges.begin(), this->edges.end(),
                     [source, target](const EdgeType& e) {
                       return e.source == source && e.target == target;
                     });
}

}  // namespace graph