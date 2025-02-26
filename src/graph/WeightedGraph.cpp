#include "../../include/graph/WeightedGraph.h"

namespace graph {

template <typename VertexType, typename WeightType>
void WeightedGraph<VertexType, WeightType>::addEdge(int source, int target,
                                                    WeightType weight) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    this->edges.emplace_back(source, target, weight);
  }
}

template <typename VertexType, typename WeightType>
WeightType WeightedGraph<VertexType, WeightType>::getEdgeWeight(int source,
                                                                int target) const {
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
void WeightedGraph<VertexType, WeightType>::setEdgeWeight(int source, int target,
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

}  // namespace graph