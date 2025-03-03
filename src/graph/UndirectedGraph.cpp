#include "../../include/graph/UndirectedGraph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void UndirectedGraph<VertexType, EdgeType>::addEdge(const VertexType& source,
                                                    const VertexType& target,
                                                    int capacity) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    // Добавляем два ребра для неориентированного графа
    this->edges.emplace_back(source, target);
    this->edges.emplace_back(target, source);
  }
}

template <typename VertexType, typename EdgeType>
void UndirectedGraph<VertexType, EdgeType>::removeEdge(
    const VertexType& source, const VertexType& target) {
  // Удаляем оба направления ребра
  this->edges.erase(
      std::remove_if(this->edges.begin(), this->edges.end(),
                     [source, target](const EdgeType& e) {
                       return (e.source == source && e.target == target) ||
                              (e.source == target && e.target == source);
                     }),
      this->edges.end());
}

template <typename VertexType, typename EdgeType>
bool UndirectedGraph<VertexType, EdgeType>::hasEdge(
    const VertexType& source, const VertexType& target) const {
  return std::any_of(this->edges.begin(), this->edges.end(),
                     [source, target](const EdgeType& e) {
                       return (e.source == source && e.target == target) ||
                              (e.source == target && e.target == source);
                     });
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
UndirectedGraph<VertexType, EdgeType>::getNeighborsIterator(
    const VertexType& vertexId) {
  std::vector<Vertex> neighbors;
  neighbors.clear();
  if (this->hasVertex(vertexId)) {
    for (const auto& edge : this->edges) {
      if (edge.source == vertexId) {
        neighbors.push_back(edge.target);
      }
    }
  }
  return neighbors.begin();
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
UndirectedGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
    const VertexType& vertexId, bool (*filter)(VertexType)) {
  std::vector<Vertex> filteredNeighbors;
  filteredNeighbors.clear();
  if (this->hasVertex(vertexId)) {
    for (const auto& edge : this->edges) {
      if (edge.source == vertexId && filter(edge.target)) {
        filteredNeighbors.push_back(edge.target);
      }
    }
  }
  return filteredNeighbors.begin();
}

template <typename VertexType, typename EdgeType>
std::vector<VertexType>
UndirectedGraph<VertexType, EdgeType>::getAdjacencyVertices(
    const VertexType& vertex) {
  std::vector<Vertex> neighbors;
  for (const auto& edge : this->edges) {
    if (edge.source == vertex) {
      neighbors.push_back(edge.target);
    }
  }
  return neighbors;
}

}  // namespace graph

template class graph::UndirectedGraph<graph::Vertex, graph::Edge>;
