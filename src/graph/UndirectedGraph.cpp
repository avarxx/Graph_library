#include "../../include/graph/UndirectedGraph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void UndirectedGraph<VertexType, EdgeType>::addEdge(int source, int target) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    // Добавляем два ребра для неориентированного графа
    this->edges.emplace_back(source, target);
    this->edges.emplace_back(target, source);
  }
}

template <typename VertexType, typename EdgeType>
void UndirectedGraph<VertexType, EdgeType>::removeEdge(int source, int target) {
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
bool UndirectedGraph<VertexType, EdgeType>::hasEdge(int source,
                                                    int target) const {
  return std::any_of(this->edges.begin(), this->edges.end(),
                     [source, target](const EdgeType& e) {
                       return (e.source == source && e.target == target) ||
                              (e.source == target && e.target == source);
                     });
}

template <typename VertexType, typename EdgeType>
std::vector<int>::iterator
UndirectedGraph<VertexType, EdgeType>::getNeighborsIterator(int vertexId) {
  static std::vector<int> neighbors;
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
std::vector<int>::iterator
UndirectedGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
    int vertexId, bool (*filter)(int)) {
  static std::vector<int> filteredNeighbors;
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