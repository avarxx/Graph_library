#ifndef BFS_VISITOR_H
#define BFS_VISITOR_H

namespace graph {

template <typename VertexType, typename EdgeType>
class BFSVisitor {
public:
    virtual ~BFSVisitor() = default;

    // Вызывается при обнаружении вершины
    virtual void discoverVertex(const VertexType& vertex) {}

    // Вызывается при посещении вершины
    virtual void visitVertex(const VertexType& vertex) {}

    // Вызывается при обнаружении ребра
    virtual void examineEdge(const EdgeType& edge) {}

    // Вызывается при посещении ребра
    virtual void treeEdge(const EdgeType& edge) {}

    // Вызывается при завершении обработки вершины
    virtual void finishVertex(const VertexType& vertex) {}
};

}  // namespace graph

#endif  // BFS_VISITOR_H