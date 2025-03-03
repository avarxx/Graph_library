#include "../../include/graph/WeightedGraph.h"

namespace graph {

template <typename VertexType, typename WeightType>
void WeightedGraph<VertexType, WeightType>::addEdge(const VertexType& source,
                                                    const VertexType& target,
                                                    WeightType weight) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    this->edges.emplace_back(source, target, weight);
  }
}

// template <typename VertexType, typename WeightType>
// void WeightedGraph<VertexType, WeightType>::addEdge(const VertexType& source,
//                                                     const VertexType& target,
//                                                     int capacity) {
//   if (this->hasVertex(source) && this->hasVertex(target) &&
//       !this->hasEdge(source, target)) {
//     this->edges.emplace_back(source, target, 1);
//   }
// }

template <typename VertexType, typename WeightType>
WeightType WeightedGraph<VertexType, WeightType>::getEdgeWeight(
    const VertexType& source, const VertexType& target) const {
  auto it =
      std::find_if(this->edges.begin(), this->edges.end(),
                   [source, target](const auto& edge) {
                     return edge.source == source && edge.target == target;
                   });

  if (it != this->edges.end()) {
    return it->weight;
  }
  throw std::out_of_range("Edge not found");
}

template <typename VertexType, typename WeightType>
void WeightedGraph<VertexType, WeightType>::setEdgeWeight(
    const VertexType& source, const VertexType& target, WeightType weight) {
  auto it =
      std::find_if(this->edges.begin(), this->edges.end(),
                   [source, target](const auto& edge) {
                     return edge.source == source && edge.target == target;
                   });

  if (it != this->edges.end()) {
    it->weight = weight;
  } else {
    throw std::out_of_range("Edge not found");
  }
}

template <typename VertexType, typename WeightType>
typename std::vector<VertexType>::iterator
WeightedGraph<VertexType, WeightType>::getNeighborsIterator(
    const VertexType& vertexId) {
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
typename std::vector<VertexType>::iterator
WeightedGraph<VertexType, WeightType>::getFilteredNeighborsIterator(
    const VertexType& vertexId, bool (*filter)(VertexType)) {
  std::vector<Vertex> filteredNeighbors;
  filteredNeighbors.clear();
  for (const auto& edge : this->edges) {
    if (edge.source == vertexId && filter(edge.target)) {
      filteredNeighbors.push_back(edge.target);
    }
  }
  return filteredNeighbors.begin();
}

template <typename VertexType, typename WeightType>
void WeightedGraph<VertexType, WeightType>::addVertex(
    const VertexType& vertex) {
  if (!hasVertex(vertex)) {
    this->vertices.emplace_back(
        vertex);  // создание вершины сразу в памяти контенера
  }
}

template <typename VertexType, typename WeightType>
void WeightedGraph<VertexType, WeightType>::removeVertex(
    const VertexType& vertex) {
  if (!hasVertex(vertex)) return;
  this->vertices.erase(
      std::remove_if(
          this->vertices.begin(), this->vertices.end(),
          [vertex](const VertexType& v) { return v.id == vertex.id; }),
      this->vertices.end());
  // remove_if перемещает все нужные вершины в конец вектора и
  // потом erase удаляет все элементы в этом диапозоне

  // Удаляем все рёбра, связанные с этой вершиной
  this->edges.erase(std::remove_if(this->edges.begin(), this->edges.end(),
                                   [vertex](const WeightedEdge<WeightType>& e) {
                                     return e.source == vertex ||
                                            e.target == vertex;
                                   }),
                    this->edges.end());
}

template <typename VertexType, typename WeightType>
void WeightedGraph<VertexType, WeightType>::removeEdge(
    const VertexType& source, const VertexType& target) {
  this->edges.erase(
      std::remove_if(this->edges.begin(), this->edges.end(),
                     [source, target](const WeightedEdge<WeightType>& e) {
                       return e.source == source && e.target == target;
                     }),
      this->edges.end());
}

template <typename VertexType, typename WeightType>
bool WeightedGraph<VertexType, WeightType>::hasVertex(
    const VertexType& id) const {
  return std::any_of(this->vertices.begin(), this->vertices.end(),
                     [id](const VertexType& v) { return v.id == id.id; });
}

template <typename VertexType, typename WeightType>
bool WeightedGraph<VertexType, WeightType>::hasEdge(
    const VertexType& source, const VertexType& target) const {
  return std::any_of(this->edges.begin(), this->edges.end(),
                     [source, target](const WeightedEdge<WeightType>& e) {
                       return e.source == source && e.target == target;
                     });
}
template <typename VertexType, typename WeightType>
std::vector<VertexType>
WeightedGraph<VertexType, WeightType>::getAdjacencyVertices(
    const VertexType& vertex) {
  return std::vector<VertexType>{1};
}

}  // namespace graph

template class graph::WeightedGraph<graph::Vertex, int>;
