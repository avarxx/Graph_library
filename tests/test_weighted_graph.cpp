#include "../include/graph/WeightedGraph.h"
#include "gtest/gtest.h"

TEST(WeightedGraphTest, AddVertex) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(WeightedGraphTest, RemoveVertex) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.removeVertex(graph::Vertex(1));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(2)));
}

TEST(WeightedGraphTest, AddEdge) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 10);
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(WeightedGraphTest, RemoveEdge) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 10);
  graph.removeEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(WeightedGraphTest, HasVertex) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(WeightedGraphTest, HasEdge) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 10);
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(WeightedGraphTest, RemoveNonexistentVertex) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  graph.removeVertex(
      graph::Vertex(2));  // Попытка удалить несуществующую вершину
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(WeightedGraphTest, RemoveNonexistentEdge) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.removeEdge(graph::Vertex(1),
                   graph::Vertex(2));  // Попытка удалить несуществующее ребро
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(WeightedGraphTest, AddDuplicateVertex) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(1));  // Попытка добавить дубликат вершины
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(WeightedGraphTest, AddDuplicateEdge) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 10);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2),
                20);  // Попытка добавить дубликат ребра
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(WeightedGraphTest, LargeGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  for (int i = 0; i < 100; ++i) {
    graph.addVertex(graph::Vertex(i));
  }
  for (int i = 0; i < 99; ++i) {
    graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1), i * 10);
  }
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(0), graph::Vertex(1)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(99), graph::Vertex(98)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(0), graph::Vertex(99)));
}