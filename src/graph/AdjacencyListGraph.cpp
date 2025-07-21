#include "../../include/graph/AdjacencyListGraph.h"

#include <memory>

#include "../../include/graph/Graph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::addVertex(
    const VertexType& vertex) {
  if (!this->hasVertex(vertex)) {
    this->vertices.emplace_back(vertex.id);
    adjacencyList[vertex] =
        std::vector<VertexType>();  // Инициализируем пустой список смежности
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::removeVertex(
    const VertexType& vertex) {
  this->vertices.erase(
      std::remove_if(
          this->vertices.begin(), this->vertices.end(),
          [vertex](const VertexType& v) { return v.id == vertex.id; }),
      this->vertices.end());

  adjacencyList.erase(vertex);

  for (auto& [vertex, neighbors] : adjacencyList) {
    neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), vertex),
                    neighbors.end());
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::addEdge(const VertexType& source,
                                                       const VertexType& target,
                                                       int capacity) {
  if (this->hasVertex(source) && this->hasVertex(target) &&
      !this->hasEdge(source, target)) {
    this->edges.emplace_back(Edge(Vertex(source.id), Vertex(target.id)));
    adjacencyList[source].push_back(
        target);  // Добавляем target в список смежности source
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyListGraph<VertexType, EdgeType>::removeEdge(
    const VertexType& source, const VertexType& target) {
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
AdjacencyListGraph<VertexType, EdgeType>::getNeighborsIterator(
    const VertexType& vertexId) {
  return adjacencyList[vertexId].begin();
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
AdjacencyListGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
    const VertexType& vertexId, bool (*filter)(VertexType)) {
  auto filteredNeighbors = std::make_unique<std::vector<VertexType>>();
  for (auto& neighbor : adjacencyList[vertexId]) {
    if (filter(neighbor)) {
      filteredNeighbors->push_back(neighbor);
    }
  }
  return filteredNeighbors->begin();
}

template <typename VertexType, typename EdgeType>
const std::unordered_map<VertexType, std::vector<VertexType>>&
AdjacencyListGraph<VertexType, EdgeType>::getAdjacencyList() {
  return adjacencyList;
}

template <typename VertexType, typename EdgeType>
bool AdjacencyListGraph<VertexType, EdgeType>::hasVertex(
    const VertexType& id) const {
  return adjacencyList.find(id) != adjacencyList.end();
}

template <typename VertexType, typename EdgeType>
bool AdjacencyListGraph<VertexType, EdgeType>::hasEdge(
    const VertexType& source, const VertexType& target) const {
  if (!hasVertex(source)) return false;
  const auto& neighbors = adjacencyList.at(source);
  return std::find(neighbors.begin(), neighbors.end(), target) !=
         neighbors.end();
}
template <typename VertexType, typename EdgeType>
std::vector<VertexType>
AdjacencyListGraph<VertexType, EdgeType>::getAdjacencyVertices(
    const VertexType& vertex) {
  return adjacencyList[vertex];
}
}  // namespace graph

template class graph::AdjacencyListGraph<graph::Vertex, graph::Edge>;
