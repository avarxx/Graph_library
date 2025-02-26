#include "gtest/gtest.h"
#include "../../include/graph/AdjacencyListGraph.h"

// Тесты для addVertex
TEST(AdjacencyListGraphTest, AddVertex_SingleVertex) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  EXPECT_TRUE(graph.hasVertex(1));
}

TEST(AdjacencyListGraphTest, AddVertex_MultipleVertices) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  EXPECT_TRUE(graph.hasVertex(1));
  EXPECT_TRUE(graph.hasVertex(2));
}

// Тесты для removeVertex
TEST(AdjacencyListGraphTest, RemoveVertex_ExistingVertex) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.removeVertex(1);
  EXPECT_FALSE(graph.hasVertex(1));
}

TEST(AdjacencyListGraphTest, RemoveVertex_NonExistingVertex) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.removeVertex(2);  // Попытка удалить несуществующую вершину
  EXPECT_TRUE(graph.hasVertex(1));
}

// Тесты для addEdge
TEST(AdjacencyListGraphTest, AddEdge_ValidEdge) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  EXPECT_TRUE(graph.hasEdge(1, 2));
}

TEST(AdjacencyListGraphTest, AddEdge_DuplicateEdge) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  graph.addEdge(1, 2);  // Попытка добавить дубликат ребра
  EXPECT_TRUE(graph.hasEdge(1, 2));
}

// Тесты для removeEdge
TEST(AdjacencyListGraphTest, RemoveEdge_ExistingEdge) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  graph.removeEdge(1, 2);
  EXPECT_FALSE(graph.hasEdge(1, 2));
}

TEST(AdjacencyListGraphTest, RemoveEdge_NonExistingEdge) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.removeEdge(1, 2);  // Попытка удалить несуществующее ребро
  EXPECT_FALSE(graph.hasEdge(1, 2));
}

// Тесты для getNeighborsIterator
TEST(AdjacencyListGraphTest, GetNeighborsIterator_SingleNeighbor) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  auto it = graph.getNeighborsIterator(1);
  EXPECT_EQ(*it, 2);
}

TEST(AdjacencyListGraphTest, GetNeighborsIterator_NoNeighbors) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  auto it = graph.getNeighborsIterator(1);
  EXPECT_EQ(it, graph.getNeighborsIterator(1, true));  // Итератор должен быть пустым
}

// Тесты для getFilteredNeighborsIterator
TEST(AdjacencyListGraphTest, GetFilteredNeighborsIterator_FilteredNeighbor) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  auto it = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; });
  EXPECT_EQ(*it, 2);
}

TEST(AdjacencyListGraphTest, GetFilteredNeighborsIterator_NoMatchingNeighbors) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  auto it = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 3; });
  EXPECT_EQ(it, graph.getFilteredNeighborsIterator(1, true));  // Итератор должен быть пустым
}

// Тесты для hasVertex
TEST(AdjacencyListGraphTest, HasVertex_ExistingVertex) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  EXPECT_TRUE(graph.hasVertex(1));
}

TEST(AdjacencyListGraphTest, HasVertex_NonExistingVertex) {
  graph::AdjacencyListGraph<> graph;
  EXPECT_FALSE(graph.hasVertex(1));
}

// Тесты для hasEdge
TEST(AdjacencyListGraphTest, HasEdge_ExistingEdge) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(1, 2);
  EXPECT_TRUE(graph.hasEdge(1, 2));
}

TEST(AdjacencyListGraphTest, HasEdge_NonExistingEdge) {
  graph::AdjacencyListGraph<> graph;
  graph.addVertex(1);
  graph.addVertex(2);
  EXPECT_FALSE(graph.hasEdge(1, 2));
}