#include "gtest/gtest.h"
#include "../include/graph/Graph.h"


// Тест на добавление вершины
TEST(GraphTest, AddVertex) {
  graph::Graph<> graph;
  graph.addVertex(1);
  EXPECT_TRUE(graph.hasVertex(1));
  EXPECT_FALSE(graph.hasVertex(2));
}

// Тест на удаление вершины
TEST(GraphTest, RemoveVertex) {
  graph::Graph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.removeVertex(1);
  EXPECT_FALSE(graph.hasVertex(1));
  EXPECT_TRUE(graph.hasVertex(2));
}

// Тест на добавление ребра
TEST(GraphTest, AddEdge) {
  graph::Graph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  EXPECT_TRUE(graph.hasEdge(1, 2));
}

// Тест на удаление ребра
TEST(GraphTest, RemoveEdge) {
  graph::Graph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  graph.removeEdge(1, 2);
  EXPECT_FALSE(graph.hasEdge(1, 2));
}

// Тест на получение списка вершин
TEST(GraphTest, GetVertices) {
  graph::Graph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  const auto& vertices = graph.getVertices();
  EXPECT_EQ(vertices.size(), 2);
  EXPECT_EQ(vertices[0].id, 1);
  EXPECT_EQ(vertices[1].id, 2);
}

// Тест на получение списка рёбер
TEST(GraphTest, GetEdges) {
  graph::Graph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  const auto& edges = graph.getEdges();
  EXPECT_EQ(edges.size(), 1);
  EXPECT_EQ(edges[0].source, 1);
  EXPECT_EQ(edges[0].target, 2);
}

// Тест на итератор по соседям вершины
TEST(GraphTest, GetNeighborsIterator) {
  graph::Graph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  auto it = graph.getNeighborsIterator(1);
  EXPECT_EQ(*it, 2);
}

// Тест на итератор с фильтром по соседям вершины
TEST(GraphTest, GetFilteredNeighborsIterator) {
  graph::Graph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  auto it = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; });
  EXPECT_EQ(*it, 2);
}

// Тест на проверку наличия вершины
TEST(GraphTest, HasVertex) {
  graph::Graph<> graph;
  graph.addVertex(1);
  EXPECT_TRUE(graph.hasVertex(1));
  EXPECT_FALSE(graph.hasVertex(2));
}

// Тест на проверку наличия ребра
TEST(GraphTest, HasEdge) {
  graph::Graph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  EXPECT_TRUE(graph.hasEdge(1, 2));
  EXPECT_FALSE(graph.hasEdge(2, 1));
}