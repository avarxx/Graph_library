#include "../../include/graph/Graph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::addVertex(const VertexType& id) {
  if (!hasVertex(id)) {
    vertices.emplace_back(id);  // создание вершины сразу в памяти контенера
  }
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::removeVertex(const VertexType& id) {
  if (!hasVertex(id)) return;
  vertices.erase(
      std::remove_if(vertices.begin(), vertices.end(),
                     [id](const VertexType& v) { return v.id == id.id; }),
      vertices.end());
  // remove_if перемещает все нужные вершины в конец вектора и
  // потом erase удаляет все элементы в этом диапозоне

  // Удаляем все рёбра, связанные с этой вершиной
  edges.erase(std::remove_if(edges.begin(), edges.end(),
                             [id](const EdgeType& e) {
                               return e.source == id || e.target == id;
                             }),
              edges.end());
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::addEdge(const VertexType& source,
                                          const VertexType& target,
                                          int capacity) {
  if (hasVertex(source) && hasVertex(target) && !hasEdge(source, target)) {
    edges.emplace_back(source, target, capacity);
  }
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::removeEdge(const VertexType& source,
                                             const VertexType& target) {
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
typename std::vector<VertexType>::iterator
Graph<VertexType, EdgeType>::getNeighborsIterator(const VertexType& vertexId) {
  std::vector<Vertex> neighbors;
  neighbors.clear();
  for (const auto& edge : edges) {
    if (edge.source == vertexId) {
      neighbors.push_back(edge.target);
    }
  }
  return neighbors.begin();
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
Graph<VertexType, EdgeType>::getFilteredNeighborsIterator(
    const VertexType& vertexId, bool (*filter)(VertexType)) {
  std::vector<Vertex> filteredNeighbors;
  filteredNeighbors.clear();
  for (const auto& edge : edges) {
    if (edge.source == vertexId && filter(edge.target)) {
      filteredNeighbors.push_back(edge.target);
    }
  }
  return filteredNeighbors.begin();
}

template <typename VertexType, typename EdgeType>
bool Graph<VertexType, EdgeType>::hasVertex(const VertexType& id) const {
  return std::any_of(vertices.begin(), vertices.end(),
                     [id](const VertexType& v) { return v.id == id.id; });
}

template <typename VertexType, typename EdgeType>
bool Graph<VertexType, EdgeType>::hasEdge(const VertexType& source,
                                          const VertexType& target) const {
  return std::any_of(edges.begin(), edges.end(),
                     [source, target](const EdgeType& e) {
                       return e.source == source && e.target == target;
                     });
}
template <typename VertexType, typename EdgeType>
std::vector<VertexType> Graph<VertexType, EdgeType>::getAdjacencyVertices(
    const VertexType& vertex) {
  std::vector<VertexType> neighbors;
  for (const auto& edge : edges) {
    if (edge.source == vertex) {
      neighbors.push_back(edge.target);
    }
  }
  return neighbors;
}

}  // namespace graph

template class graph::Graph<graph::Vertex, graph::Edge>;
template class graph::Graph<graph::Vertex, graph::WeightedEdge<int>>;
