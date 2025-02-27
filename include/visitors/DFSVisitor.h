#ifndef DFS_VISITOR_H
#define DFS_VISITOR_H

namespace graph {

template <typename VertexType, typename EdgeType>
class DFSVisitor {
public:
    virtual ~DFSVisitor() = default;

    virtual void discoverVertex(const VertexType& vertex) {}

    virtual void visitVertex(const VertexType& vertex) {}

    virtual void examineEdge(const EdgeType& edge) {}

    virtual void treeEdge(const EdgeType& edge) {}

    virtual void finishVertex(const VertexType& vertex) {}
};

}  // namespace graph

#endif  // DFS_VISITOR_H