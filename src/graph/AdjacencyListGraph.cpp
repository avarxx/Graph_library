#include "../../include/graph/AdjacencyListGraph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::addVertex(int id) {
  if (!this->hasVertex(id)) {
    this->vertices.emplace_back(id);
    adjacencyList[id] =
        std::vector<int>();  // Инициализируем пустой список смежности
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::removeVertex(int id) {
  if constexpr (std::is_same_v<VertexType, int>) {
    // Для int
    this->vertices.erase(
        std::remove(this->vertices.begin(), this->vertices.end(), id),
        this->vertices.end());
  } else {
    // Для graph::Vertex
    this->vertices.erase(
        std::remove_if(this->vertices.begin(), this->vertices.end(),
                       [id](const VertexType& v) { return v.id == id; }),
        this->vertices.end());
  }

  adjacencyList.erase(id);

  for (auto& [vertex, neighbors] : adjacencyList) {
    neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), id),
                    neighbors.end());
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::addEdge(int source, int target) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    this->edges.emplace_back(source, target);
    adjacencyList[source].push_back(
        target);  // Добавляем target в список смежности source
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::removeEdge(int source,
                                                          int target) {
  this->edges.erase(std::remove_if(this->edges.begin(), this->edges.end(),
                                   [source, target](const EdgeType& e) {
                                     return e.source == source &&
                                            e.target == target;
                                   }),
                    this->edges.end());

  // Удаляем target из списка смежности source
  auto& neighbors = adjacencyList[source];
  neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), target),
                  neighbors.end());
}

template <typename VertexType, typename EdgeType>
std::vector<int>::iterator
AdjacencyListGraph<VertexType, EdgeType>::getNeighborsIterator(int vertexId) {
  return adjacencyList[vertexId].begin();
}

template <typename VertexType, typename EdgeType>
std::vector<int>::iterator
AdjacencyListGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
    int vertexId, bool (*filter)(int)) {
  static std::vector<int> filteredNeighbors;
  filteredNeighbors.clear();
  for (int neighbor : adjacencyList[vertexId]) {
    if (filter(neighbor)) {
      filteredNeighbors.push_back(neighbor);
    }
  }
  return filteredNeighbors.begin();
}

template <typename VertexType, typename EdgeType>
const std::unordered_map<int, std::vector<int>>&
AdjacencyListGraph<VertexType, EdgeType>::getAdjacencyList() const {
  return adjacencyList;
}

template <typename VertexType, typename EdgeType>
bool AdjacencyListGraph<VertexType, EdgeType>::hasVertex(int id) const {
  return adjacencyList.find(id) != adjacencyList.end();
}

template <typename VertexType, typename EdgeType>
bool AdjacencyListGraph<VertexType, EdgeType>::hasEdge(int source,
                                                       int target) const {
  if (!hasVertex(source)) return false;
  const auto& neighbors = adjacencyList.at(source);
  return std::find(neighbors.begin(), neighbors.end(), target) !=
         neighbors.end();
}

}  // namespace graph

template class graph::AdjacencyListGraph<graph::Vertex, graph::Edge>;
template class graph::AdjacencyListGraph<int, graph::Edge>;