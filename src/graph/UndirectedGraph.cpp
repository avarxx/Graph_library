#include "../../include/graph/UndirectedGraph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void UndirectedGraph<VertexType, EdgeType>::addEdge(const Vertex& source, const Vertex& target) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    // Добавляем два ребра для неориентированного графа
    this->edges.emplace_back(source, target);
    this->edges.emplace_back(target, source);
  }
}

template <typename VertexType, typename EdgeType>
void UndirectedGraph<VertexType, EdgeType>::removeEdge(const Vertex& source, const Vertex& target) {
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
bool UndirectedGraph<VertexType, EdgeType>::hasEdge(const Vertex& source,
  const Vertex& target) const {
  return std::any_of(this->edges.begin(), this->edges.end(),
                     [source, target](const EdgeType& e) {
                       return (e.source == source && e.target == target) ||
                              (e.source == target && e.target == source);
                     });
}

template <typename VertexType, typename EdgeType>
typename std::vector<Vertex>::iterator
UndirectedGraph<VertexType, EdgeType>::getNeighborsIterator(const Vertex& vertexId) {
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
typename std::vector<Vertex>::iterator
UndirectedGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
  const Vertex& vertexId, bool (*filter)(Vertex)) {
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

}  // namespace graph

template class graph::UndirectedGraph<graph::Vertex, graph::Edge>;
// template class graph::UndirectedGraph<int, graph::Edge>;