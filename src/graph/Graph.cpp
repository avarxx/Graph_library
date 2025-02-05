#include "graph/Graph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::addVertex(int id) {
  if (!hasVertex(id)) {
    vertices.emplace_back(id);
  }
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::removeVertex(int id) {
  vertices.erase(
      std::remove_if(vertices.begin(), vertices.end(),
                     [id](const VertexType& v) { return v.id == id; }),
      vertices.end());

  // Удаляем все рёбра, связанные с этой вершиной
  edges.erase(std::remove_if(edges.begin(), edges.end(),
                             [id](const EdgeType& e) {
                               return e.source == id || e.target == id;
                             }),
              edges.end());
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::addEdge(int source, int target) {
  if (hasVertex(source) && hasVertex(target) && !hasEdge(source, target)) {
    edges.emplace_back(source, target);
  }
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::removeEdge(int source, int target) {
  edges.erase(std::remove_if(edges.begin(), edges.end(),
                             [source, target](const EdgeType& e) {
                               return e.source == source && e.target == target;
                             }),
              edges.end());
}

template <typename VertexType, typename EdgeType>
const std::vector<VertexType>& Graph<VertexType, EdgeType>::getVertices()
    const {
  return vertices;
}

template <typename VertexType, typename EdgeType>
const std::vector<EdgeType>& Graph<VertexType, EdgeType>::getEdges() const {
  return edges;
}

template <typename VertexType, typename EdgeType>
std::vector<int>::iterator Graph<VertexType, EdgeType>::getNeighborsIterator(
    int vertexId) {
  static std::vector<int> neighbors;
  neighbors.clear();
  for (const auto& edge : edges) {
    if (edge.source == vertexId) {
      neighbors.push_back(edge.target);
    }
  }
  return neighbors.begin();
}

template <typename VertexType, typename EdgeType>
std::vector<int>::iterator
Graph<VertexType, EdgeType>::getFilteredNeighborsIterator(int vertexId,
                                                          bool (*filter)(int)) {
  static std::vector<int> filteredNeighbors;
  filteredNeighbors.clear();
  for (const auto& edge : edges) {
    if (edge.source == vertexId && filter(edge.target)) {
      filteredNeighbors.push_back(edge.target);
    }
  }
  return filteredNeighbors.begin();
}

template <typename VertexType, typename EdgeType>
bool Graph<VertexType, EdgeType>::hasVertex(int id) const {
  return std::any_of(vertices.begin(), vertices.end(),
                     [id](const VertexType& v) { return v.id == id; });
}

template <typename VertexType, typename EdgeType>
bool Graph<VertexType, EdgeType>::hasEdge(int source, int target) const {
  return std::any_of(edges.begin(), edges.end(),
                     [source, target](const EdgeType& e) {
                       return e.source == source && e.target == target;
                     });
}

}  // namespace graph