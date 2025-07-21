#include "../../include/graph/AdjacencyMatrixGraph.h"

namespace graph {

template <typename VertexType, typename EdgeType>
size_t AdjacencyMatrixGraph<VertexType, EdgeType>::getVertexIndex(
    const VertexType& id) const {
  auto it = vertexToIndex.find(id);
  if (it != vertexToIndex.end()) {
    return it->second;
  }
  throw std::out_of_range("Vertex not found");
}

template <typename VertexType, typename EdgeType>
void AdjacencyMatrixGraph<VertexType, EdgeType>::addVertex(
    const VertexType& id) {
  if (!hasVertex(id)) {
    this->vertices.emplace_back(id);

    // Добавляем новую вершину в матрицу смежности
    size_t newIndex = adjacencyMatrix.size();
    vertexToIndex[id] = newIndex;
    indexToVertex[newIndex] = id;

    // Расширяем матрицу смежности
    for (auto& row : adjacencyMatrix) {
      row.push_back(false);  // Добавляем новый столбец
    }
    adjacencyMatrix.push_back(
        std::vector<bool>(newIndex + 1, false));  // Добавляем новую строку
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyMatrixGraph<VertexType, EdgeType>::removeVertex(
    const VertexType& id) {
  if (hasVertex(id)) {
    size_t index = getVertexIndex(id);

    // Удаляем вершину из списка вершин
    this->vertices.erase(
        std::remove_if(this->vertices.begin(), this->vertices.end(),
                       [id](const VertexType& v) { return v.id == id.id; }),
        this->vertices.end());

    // Удаляем строку и столбец из матрицы смежности
    adjacencyMatrix.erase(adjacencyMatrix.begin() + index);
    for (auto& row : adjacencyMatrix) {
      row.erase(row.begin() + index);
    }

    // Обновляем индексы оставшихся вершин
    vertexToIndex.erase(id);
    for (auto& [vertexId, vertexIndex] : vertexToIndex) {
      if (vertexIndex > index) {
        vertexIndex--;
      }
    }
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyMatrixGraph<VertexType, EdgeType>::addEdge(
    const VertexType& source, const VertexType& target, int capacity) {
  if (hasVertex(source) && hasVertex(target) && !hasEdge(source, target)) {
    this->edges.emplace_back(source, target);
    size_t sourceIndex = getVertexIndex(source);
    size_t targetIndex = getVertexIndex(target);
    adjacencyMatrix[sourceIndex][targetIndex] = true;
  }
}

template <typename VertexType, typename EdgeType>
void AdjacencyMatrixGraph<VertexType, EdgeType>::removeEdge(
    const VertexType& source, const VertexType& target) {
  if (hasEdge(source, target)) {
    this->edges.erase(std::remove_if(this->edges.begin(), this->edges.end(),
                                     [source, target](const EdgeType& e) {
                                       return e.source == source &&
                                              e.target == target;
                                     }),
                      this->edges.end());

    size_t sourceIndex = getVertexIndex(source);
    size_t targetIndex = getVertexIndex(target);
    adjacencyMatrix[sourceIndex][targetIndex] = false;
  }
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
AdjacencyMatrixGraph<VertexType, EdgeType>::getNeighborsIterator(
    const VertexType& vertexId) {
  std::vector<Vertex> neighbors;
  neighbors.clear();
  if (hasVertex(vertexId)) {
    size_t index = getVertexIndex(vertexId);
    for (size_t i = 0; i < adjacencyMatrix[index].size(); ++i) {
      if (adjacencyMatrix[index][i]) {
        neighbors.push_back(indexToVertex[i]);
      }
    }
  }
  return neighbors.begin();
}

template <typename VertexType, typename EdgeType>
typename std::vector<VertexType>::iterator
AdjacencyMatrixGraph<VertexType, EdgeType>::getFilteredNeighborsIterator(
    const VertexType& vertexId, bool (*filter)(VertexType)) {
  static std::vector<Vertex> filteredNeighbors;
  filteredNeighbors.clear();
  if (hasVertex(vertexId)) {
    size_t index = getVertexIndex(vertexId);
    for (size_t i = 0; i < adjacencyMatrix[index].size(); ++i) {
      if (adjacencyMatrix[index][i] && filter(indexToVertex[i])) {
        filteredNeighbors.push_back(indexToVertex[i]);
      }
    }
  }
  return filteredNeighbors.begin();
}

template <typename VertexType, typename EdgeType>
bool AdjacencyMatrixGraph<VertexType, EdgeType>::hasVertex(
    const VertexType& id) const {
  return vertexToIndex.find(id) != vertexToIndex.end();
}

template <typename VertexType, typename EdgeType>
bool AdjacencyMatrixGraph<VertexType, EdgeType>::hasEdge(
    const VertexType& source, const VertexType& target) const {
  if (!hasVertex(source) || !hasVertex(target)) return false;
  size_t sourceIndex = getVertexIndex(source);
  size_t targetIndex = getVertexIndex(target);
  return adjacencyMatrix[sourceIndex][targetIndex];
}
template <typename VertexType, typename EdgeType>
std::vector<VertexType>
AdjacencyMatrixGraph<VertexType, EdgeType>::getAdjacencyVertices(
    const VertexType& vertex) {
  std::vector<VertexType> adjacencyEdges;
  for (int i = 0; i < adjacencyMatrix[vertex.id - 1].size(); i++) {
    if (adjacencyMatrix[vertex.id - 1][i]) {
      adjacencyEdges.push_back(Vertex(i + 1));
    }
  }
  return adjacencyEdges;
}

}  // namespace graph

template class graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge>;
