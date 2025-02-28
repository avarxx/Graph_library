#include "../../include/graph/Graph.h"

namespace graph
{

  template <typename VertexType, typename EdgeType>
  void Graph<VertexType, EdgeType>::addVertex(const Vertex& id)
  {
    if (!hasVertex(id))
    {
      vertices.emplace_back(id); // создание вершины сразу в памяти контенера
    }
  }

  template <typename VertexType, typename EdgeType>
  void Graph<VertexType, EdgeType>::removeVertex(const Vertex& id)
  {
    if(!hasVertex(id))
      return;
    vertices.erase(
        std::remove_if(vertices.begin(), vertices.end(), [id](const VertexType &v)
                       { return v.id == id.id; }),
        vertices.end());
    // remove_if перемещает все нужные вершины в конец вектора и
    // потом erase удаляет все элементы в этом диапозоне

    // Удаляем все рёбра, связанные с этой вершиной
    edges.erase(std::remove_if(edges.begin(), edges.end(), [id](const EdgeType &e)
                               { return e.source == id || e.target == id; }),
                edges.end());
  }

  template <typename VertexType, typename EdgeType>
  void Graph<VertexType, EdgeType>::addEdge(const Vertex& source, const Vertex& target)
  {
    if (hasVertex(source) && hasVertex(target) && !hasEdge(source, target))
    {
      edges.emplace_back(source, target);
    }
  }

  template <typename VertexType, typename EdgeType>
  void Graph<VertexType, EdgeType>::removeEdge(const Vertex& source, const Vertex& target)
  {
    edges.erase(std::remove_if(edges.begin(), edges.end(), [source, target](const EdgeType &e)
                               { return e.source == source && e.target == target; }),
                edges.end());
  }

  template <typename VertexType, typename EdgeType>
  const std::vector<VertexType> &Graph<VertexType, EdgeType>::getVertices() const
  {
    return vertices;
  }

  template <typename VertexType, typename EdgeType>
  const std::vector<EdgeType> &Graph<VertexType, EdgeType>::getEdges() const
  {
    return edges;
  }

  template <typename VertexType, typename EdgeType>
  typename std::vector<VertexType>::iterator Graph<VertexType, EdgeType>::getNeighborsIterator(
    const Vertex& vertexId)
  {
    std::vector<Vertex> neighbors;
    neighbors.clear();
    for (const auto &edge : edges)
    {
      if (edge.source == vertexId)
      {
        neighbors.push_back(edge.target);
      }
    }
    return neighbors.begin();
  }

  template <typename VertexType, typename EdgeType>
  typename std::vector<VertexType>::iterator
  Graph<VertexType, EdgeType>::getFilteredNeighborsIterator(const Vertex& vertexId,
                                                            bool (*filter)(Vertex))
  {
    std::vector<Vertex> filteredNeighbors;
    filteredNeighbors.clear();
    for (const auto &edge : edges)
    {
      if (edge.source == vertexId && filter(edge.target))
      {
        filteredNeighbors.push_back(edge.target);
      }
    }
    return filteredNeighbors.begin();
  }

  template <typename VertexType, typename EdgeType>
  bool Graph<VertexType, EdgeType>::hasVertex(const Vertex& id) const
  {
    return std::any_of(vertices.begin(), vertices.end(),
                       [id](const VertexType &v)
                       { return v.id == id.id; });
  }

  template <typename VertexType, typename EdgeType>
  bool Graph<VertexType, EdgeType>::hasEdge(const Vertex& source, const Vertex& target) const
  {
    return std::any_of(edges.begin(), edges.end(),
                       [source, target](const EdgeType &e)
                       {
                         return e.source == source && e.target == target;
                       });
  }

} // namespace graph

template class graph::Graph<graph::Vertex, graph::Edge>;
// template class graph::Graph<int, graph::Edge>;