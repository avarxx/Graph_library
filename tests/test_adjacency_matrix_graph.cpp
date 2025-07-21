#include "../include/graph/AdjacencyMatrixGraph.h"
#include "gtest/gtest.h"

TEST(AdjacencyMatrixGraphTest, AddVertex) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(AdjacencyMatrixGraphTest, RemoveVertex) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.removeVertex(graph::Vertex(1));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(2)));
}

TEST(AdjacencyMatrixGraphTest, AddEdge) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(AdjacencyMatrixGraphTest, RemoveEdge) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.removeEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(AdjacencyMatrixGraphTest, HasVertex) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(AdjacencyMatrixGraphTest, HasEdge) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(AdjacencyMatrixGraphTest, RemoveNonexistentVertex) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.removeVertex(
      graph::Vertex(2));  // Попытка удалить несуществующую вершину
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(AdjacencyMatrixGraphTest, RemoveNonexistentEdge) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.removeEdge(graph::Vertex(1),
                   graph::Vertex(2));  // Попытка удалить несуществующее ребро
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(AdjacencyMatrixGraphTest, AddDuplicateVertex) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(1));  // Попытка добавить дубликат вершины
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(AdjacencyMatrixGraphTest, AddDuplicateEdge) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(1),
                graph::Vertex(2));  // Попытка добавить дубликат ребра
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(AdjacencyMatrixGraphTest, LargeGraph) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  for (int i = 0; i < 100; ++i) {
    graph.addVertex(graph::Vertex(i));
  }
  for (int i = 0; i < 99; ++i) {
    graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1));
  }
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(0), graph::Vertex(1)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(99), graph::Vertex(98)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(0), graph::Vertex(99)));
}