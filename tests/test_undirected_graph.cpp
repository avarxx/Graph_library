#include "../include/graph/UndirectedGraph.h"
#include "gtest/gtest.h"

TEST(UndirectedGraphTest, AddVertex) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(UndirectedGraphTest, RemoveVertex) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.removeVertex(graph::Vertex(1));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(2)));
}

TEST(UndirectedGraphTest, AddEdge) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_TRUE(graph.hasEdge(
      graph::Vertex(2),
      graph::Vertex(1)));  // В неориентированном графе ребро двунаправленное
}

TEST(UndirectedGraphTest, RemoveEdge) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.removeEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_FALSE(graph.hasEdge(
      graph::Vertex(2),
      graph::Vertex(
          1)));  // В неориентированном графе удаляется оба направления
}

TEST(UndirectedGraphTest, HasVertex) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(UndirectedGraphTest, HasEdge) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_TRUE(graph.hasEdge(
      graph::Vertex(2),
      graph::Vertex(1)));  // В неориентированном графе ребро двунаправленное
}

TEST(UndirectedGraphTest, RemoveNonexistentVertex) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.removeVertex(
      graph::Vertex(2));  // Попытка удалить несуществующую вершину
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(UndirectedGraphTest, RemoveNonexistentEdge) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.removeEdge(graph::Vertex(1),
                   graph::Vertex(2));  // Попытка удалить несуществующее ребро
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_FALSE(graph.hasEdge(
      graph::Vertex(2),
      graph::Vertex(
          1)));  // В неориентированном графе удаляется оба направления
}

TEST(UndirectedGraphTest, AddDuplicateVertex) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(1));  // Попытка добавить дубликат вершины
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(UndirectedGraphTest, AddDuplicateEdge) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(1),
                graph::Vertex(2));  // Попытка добавить дубликат ребра
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
  EXPECT_TRUE(graph.hasEdge(
      graph::Vertex(2),
      graph::Vertex(1)));  // В неориентированном графе ребро двунаправленное
}

TEST(UndirectedGraphTest, GetNeighborsOfNonexistentVertex) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  auto neighbors = graph.getNeighborsIterator(
      graph::Vertex(1));  // Попытка получить соседей несуществующей вершины
  EXPECT_EQ(neighbors, graph.getNeighborsIterator(
                           graph::Vertex(1)));  // Итератор должен быть пустым
}

TEST(UndirectedGraphTest, LargeGraph) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  for (int i = 0; i < 100; ++i) {
    graph.addVertex(graph::Vertex(i));
  }
  for (int i = 0; i < 99; ++i) {
    graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1));
  }
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(0), graph::Vertex(1)));
  EXPECT_TRUE(graph.hasEdge(graph::Vertex(99), graph::Vertex(98)));
  EXPECT_FALSE(graph.hasEdge(graph::Vertex(0), graph::Vertex(99)));
}
