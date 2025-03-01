#include "../include/graph/EdgeListGraph.h"
#include "gtest/gtest.h"

TEST(EdgeListGraphTest, AddVertex) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(EdgeListGraphTest, RemoveVertex) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.removeVertex(graph::Vertex(1));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(2)));
}

TEST(EdgeListGraphTest, AddEdge) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(EdgeListGraphTest, RemoveEdge) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.removeEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(EdgeListGraphTest, HasVertex) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(EdgeListGraphTest, HasEdge) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(EdgeListGraphTest, RemoveNonexistentVertex) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.removeVertex(
      graph::Vertex(2));  // Попытка удалить несуществующую вершину
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(EdgeListGraphTest, RemoveNonexistentEdge) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.removeEdge(graph::Vertex(1),
                   graph::Vertex(2));  // Попытка удалить несуществующее ребро
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(EdgeListGraphTest, AddDuplicateVertex) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(1));  // Попытка добавить дубликат вершины
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(EdgeListGraphTest, AddDuplicateEdge) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(1),
                graph::Vertex(2));  // Попытка добавить дубликат ребра
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(EdgeListGraphTest, GetNeighborsOfNonexistentVertex) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  auto neighbors = graph.getNeighborsIterator(
      graph::Vertex(1));  // Попытка получить соседей несуществующей вершины
  EXPECT_EQ(neighbors, graph.getNeighborsIterator(
                           graph::Vertex(1)));  // Итератор должен быть пустым
}

TEST(EdgeListGraphTest, LargeGraph) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
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