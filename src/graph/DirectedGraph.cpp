#include "../../include/graph/DirectedGraph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void DirectedGraph<VertexType, EdgeType>::addEdge(const VertexType& source,
                                                  const VertexType& target,
                                                  int capacity) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    this->edges.emplace_back(source, target);
  }
}

template <typename VertexType, typename EdgeType>
void DirectedGraph<VertexType, EdgeType>::removeEdge(const VertexType& source,
                                                     const VertexType& target) {
  this->edges.erase(std::remove_if(this->edges.begin(), this->edges.end(),
                                   [source, target](const EdgeType& e) {
                                     return e.source == source &&
                                            e.target == target;
                                   }),
                    this->edges.end());
}

template <typename VertexType, typename EdgeType>
bool DirectedGraph<VertexType, EdgeType>::hasEdge(
    const VertexType& source, const VertexType& target) const {
  return std::any_of(this->edges.begin(), this->edges.end(),
                     [source, target](const EdgeType& e) {
                       return e.source == source && e.target == target;
                     });
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
DirectedGraph<VertexType, EdgeType>::getNeighborsIterator(
    const VertexType& vertexId) {
  std::vector<VertexType> neighbors;
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
DirectedGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
    const VertexType& vertexId, bool (*filter)(VertexType)) {
  std::vector<VertexType> filteredNeighbors;
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
DirectedGraph<VertexType, EdgeType>::getAdjacencyVertices(
    const VertexType& vertex) {
  std::vector<VertexType> neighbors;
  for (const auto& edge : this->edges) {
    if (edge.source == vertex) {
      neighbors.push_back(edge.target);
    }
  }
  return neighbors;
}

}  // namespace graph

template class graph::DirectedGraph<graph::Vertex, graph::Edge>;
