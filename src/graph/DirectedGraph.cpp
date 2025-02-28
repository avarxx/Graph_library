#include "../../include/graph/DirectedGraph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void DirectedGraph<VertexType, EdgeType>::addEdge(const Vertex& source, const Vertex& target) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    this->edges.emplace_back(source, target);
  }
}

template <typename VertexType, typename EdgeType>
void DirectedGraph<VertexType, EdgeType>::removeEdge(const Vertex& source, const Vertex& target) {
  this->edges.erase(
      std::remove_if(this->edges.begin(), this->edges.end(),
                     [source, target](const EdgeType& e) {
                       return e.source == source && e.target == target;
                     }),
      this->edges.end());
}

template <typename VertexType, typename EdgeType>
bool DirectedGraph<VertexType, EdgeType>::hasEdge(const Vertex& source, const Vertex& target) const {
  return std::any_of(this->edges.begin(), this->edges.end(),
                     [source, target](const EdgeType& e) {
                       return e.source == source && e.target == target;
                     });
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
DirectedGraph<VertexType, EdgeType>::getNeighborsIterator(const Vertex& vertexId) {
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
  const Vertex& vertexId, bool (*filter)(Vertex)) {
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

}  // namespace graph

template class graph::DirectedGraph<graph::Vertex, graph::Edge>;
// template class graph::DirectedGraph<int, graph::Edge>;