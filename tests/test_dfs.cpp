#include "../include/algorithms/DFS.h"
#include "../include/graph/AdjacencyListGraph.h"
#include "../include/graph/AdjacencyMatrixGraph.h"
#include "../include/graph/DirectedGraph.h"
#include "../include/graph/EdgeListGraph.h"
#include "../include/graph/UndirectedGraph.h"
#include "../include/graph/WeightedGraph.h"
#include "gtest/gtest.h"

TEST(DFS_TEST, AdjacencyListNoVertex) {
  graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
}

TEST(DFS_TEST, AdjacencyListNoMultipleVertex) {
  graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(4), graph::Vertex(5));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
  EXPECT_EQ(d.find(graph::Vertex(5)), d.end());
}

TEST(DFS_TEST, AdjacencyMatrixNoVertex) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
}

TEST(DFS_TEST, AdjacencyMatrixNoMultipleVertex) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(4), graph::Vertex(5));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
  EXPECT_EQ(d.find(graph::Vertex(5)), d.end());
}

TEST(DFS_TEST, DirectedNoVertex) {
  graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
}

TEST(DFS_TEST, DirectedNoMultipleVertex) {
  graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(4), graph::Vertex(5));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
  EXPECT_EQ(d.find(graph::Vertex(5)), d.end());
}

TEST(DFS_TEST, EdgeListNoVertex) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
}

TEST(DFS_TEST, EdgeListNoMultipleVertex) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(4), graph::Vertex(5));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
  EXPECT_EQ(d.find(graph::Vertex(5)), d.end());
}

TEST(DFS_TEST, UndirectedNoVertex) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
}

TEST(DFS_TEST, UndirectedNoMultipleVertex) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(4), graph::Vertex(5));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::DFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d.find(graph::Vertex(4)), d.end());
  EXPECT_NE(d.find(graph::Vertex(1)), d.end());
  EXPECT_EQ(d.find(graph::Vertex(5)), d.end());
}
