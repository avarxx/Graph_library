#include "../../include/graph/WeightedGraph.h"

namespace graph {

template <typename VertexType, typename WeightType>
void WeightedGraph<VertexType, WeightType>::addEdge(const Vertex& source, const Vertex& target,
                                                    WeightType weight) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    this->edges.emplace_back(source, target, weight);
  }
}

template <typename VertexType, typename WeightType>
WeightType WeightedGraph<VertexType, WeightType>::getEdgeWeight(const Vertex& source,
  const Vertex& target) const {
  auto it = std::find_if(
      this->edges.begin(), this->edges.end(), [source, target](const auto& edge) {
        return edge.source == source && edge.target == target;
      });

  if (it != this->edges.end()) {
    return it->weight;
  }
  throw std::out_of_range("Edge not found");
}

template <typename VertexType, typename WeightType>
void WeightedGraph<VertexType, WeightType>::setEdgeWeight(const Vertex& source, const Vertex& target,
                                                          WeightType weight) {
  auto it = std::find_if(
      this->edges.begin(), this->edges.end(), [source, target](const auto& edge) {
        return edge.source == source && edge.target == target;
      });

  if (it != this->edges.end()) {
    it->weight = weight;
  } else {
    throw std::out_of_range("Edge not found");
  }
}

template <typename VertexType, typename WeightType>
typename std::vector<Vertex>::iterator WeightedGraph<VertexType, WeightType>::getNeighborsIterator(const Vertex& vertexId) {
  std::vector<Vertex> neighbors;
  neighbors.clear();
  for (const auto& edge : this->edges) {
    if (edge.source == vertexId) {
      neighbors.push_back(edge.target);
    }
  }
  return neighbors.begin();
}

template <typename VertexType, typename WeightType>
typename std::vector<Vertex>::iterator WeightedGraph<VertexType, WeightType>::getFilteredNeighborsIterator(
  const Vertex& vertexId, bool (*filter)(Vertex)) {
  std::vector<Vertex> filteredNeighbors;
  filteredNeighbors.clear();
  for (const auto& edge : this->edges) {
    if (edge.source == vertexId && filter(edge.target)) {
      filteredNeighbors.push_back(edge.target);
    }
  }
  return filteredNeighbors.begin();
}

}  // namespace graph

template class graph::WeightedGraph<graph::Vertex, graph::Edge>;
// template class graph::WeightedGraph<int, graph::Edge>;