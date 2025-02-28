#include "../../include/graph/AdjacencyListGraph.h"
#include "../../include/graph/Graph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::addVertex(const Vertex& vertex) {
  if (!this->hasVertex(vertex)) {
    this->vertices.emplace_back(vertex.id);
    adjacencyList[vertex] =
        std::vector<VertexType>();  // Инициализируем пустой список смежности
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::removeVertex(const Vertex& vertex) {
  // if constexpr (std::is_same_v<VertexType, int>) {
  //   // Для int
  //   this->vertices.erase(
  //       std::remove(this->vertices.begin(), this->vertices.end(), id),
  //       this->vertices.end());
  // } else {
    // Для graph::Vertex
    this->vertices.erase(
        std::remove_if(this->vertices.begin(), this->vertices.end(),
                       [vertex](const VertexType& v) { return v.id == vertex.id; }),
        this->vertices.end());
  //}

  adjacencyList.erase(vertex);

  for (auto& [vertex, neighbors] : adjacencyList) {
    neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), vertex),
                    neighbors.end());
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::addEdge(const Vertex& source, const Vertex& target) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    this->edges.emplace_back(Edge(Vertex(source.id), Vertex(target.id)));
    adjacencyList[source].push_back(
        target);  // Добавляем target в список смежности source
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::removeEdge(const Vertex& source,
                                                          const Vertex& target) {
  this->edges.erase(std::remove_if(this->edges.begin(), this->edges.end(),
                                   [source, target](const EdgeType& e) {
                                     return e.source.id == source.id &&
                                            e.target.id == target.id;
                                   }),
                    this->edges.end());

  // Удаляем target из списка смежности source
  auto& neighbors = adjacencyList[source];
  neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), target),
                  neighbors.end());
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
AdjacencyListGraph<VertexType, EdgeType>::getNeighborsIterator(const Vertex& vertexId) {
  return adjacencyList[vertexId].begin();
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
AdjacencyListGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
  const Vertex& vertexId, bool (*filter)(Vertex)) {
  std::vector<Vertex> filteredNeighbors;
  filteredNeighbors.clear();
  for (auto& neighbor : adjacencyList[vertexId]) {
    if (filter(neighbor)) {
      filteredNeighbors.push_back(neighbor);
    }
  }
  return filteredNeighbors.begin();
}

template <typename VertexType, typename EdgeType>
const std::unordered_map<Vertex, std::vector<Vertex>>&
AdjacencyListGraph<VertexType, EdgeType>::getAdjacencyList() const {
  return adjacencyList;
}

template <typename VertexType, typename EdgeType>
bool AdjacencyListGraph<VertexType, EdgeType>::hasVertex(const Vertex& id) const {
  return adjacencyList.find(id) != adjacencyList.end();
}

template <typename VertexType, typename EdgeType>
bool AdjacencyListGraph<VertexType, EdgeType>::hasEdge(const Vertex& source,
  const Vertex& target) const {
  if (!hasVertex(source)) return false;
  const auto& neighbors = adjacencyList.at(source);
  return std::find(neighbors.begin(), neighbors.end(), target) !=
         neighbors.end();
}

}  // namespace graph

template class graph::AdjacencyListGraph<graph::Vertex, graph::Edge>;
//template class graph::AdjacencyListGraph<int, graph::Edge>;