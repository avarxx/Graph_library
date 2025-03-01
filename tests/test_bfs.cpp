#include "../include/algorithms/BFS.h"
#include "../include/graph/AdjacencyListGraph.h"
#include "../include/graph/AdjacencyMatrixGraph.h"
#include "../include/graph/DirectedGraph.h"
#include "../include/graph/UndirectedGraph.h"
#include "../include/graph/WeightedGraph.h"
#include "gtest/gtest.h"

TEST(BFS_TEST, AdjacencyListThroughOne) {
  graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 1);
}

TEST(BFS_TEST, AdjacencyListEasy) {
  graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 2);
}

TEST(BFS_TEST, AdjacencyMatrixThroughOne) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 1);
}

TEST(BFS_TEST, AdjacencyMatrixEasy) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 2);
}

TEST(BFS_TEST, DirectedGraphThroughOne) {
  graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 1);
}

TEST(BFS_TEST, DirectedGraphEasy) {
  graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 2);
}

TEST(BFS_TEST, EdgeListThroughOne) {
  graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 1);
}

TEST(BFS_TEST, EdgeListEasy) {
  graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 2);
}

TEST(BFS_TEST, UndirectedGraphThroughOne) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 1);
}

TEST(BFS_TEST, UndirectedGraphEasy) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph::DefaultVisitor<graph::Vertex, graph::Edge> visitor;
  auto d = graph::BFS(graph, graph::Vertex(1), visitor);
  EXPECT_EQ(d[1], 0);
  EXPECT_EQ(d[2], 1);
  EXPECT_EQ(d[3], 2);
}
