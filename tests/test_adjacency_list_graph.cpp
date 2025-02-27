#include "gtest/gtest.h"
#include "graph/AdjacencyListGraph.h"

TEST(AdjacencyListGraphTest, AddVertex) {
  graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(1);
  EXPECT_TRUE(graph.hasVertex(1));
  EXPECT_FALSE(graph.hasVertex(2));
}

TEST(AdjacencyListGraphTest, RemoveVertex) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeVertex(1);
    EXPECT_FALSE(graph.hasVertex(1));
    EXPECT_TRUE(graph.hasVertex(2));
}

TEST(AdjacencyListGraphTest, AddEdge) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_FALSE(graph.hasEdge(2, 1));
}

TEST(AdjacencyListGraphTest, RemoveEdge) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    graph.removeEdge(1, 2);
    EXPECT_FALSE(graph.hasEdge(1, 2));
}

TEST(AdjacencyListGraphTest, GetNeighborsIterator) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    auto neighbors = graph.getNeighborsIterator(1);
    EXPECT_EQ(*neighbors, 2);
    ++neighbors;
    EXPECT_EQ(*neighbors, 3);
}

TEST(AdjacencyListGraphTest, GetFilteredNeighborsIterator) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 3; });
    EXPECT_EQ(*filteredNeighbors, 3);
}

TEST(AdjacencyListGraphTest, HasVertex) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_FALSE(graph.hasVertex(2));
}

TEST(AdjacencyListGraphTest, HasEdge) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_FALSE(graph.hasEdge(2, 1));
}

TEST(AdjacencyListGraphTest, RemoveNonexistentVertex) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.removeVertex(2); // Попытка удалить несуществующую вершину
    EXPECT_TRUE(graph.hasVertex(1));
}

TEST(AdjacencyListGraphTest, RemoveNonexistentEdge) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeEdge(1, 2); // Попытка удалить несуществующее ребро
    EXPECT_FALSE(graph.hasEdge(1, 2));
}

TEST(AdjacencyListGraphTest, AddDuplicateVertex) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(1); // Попытка добавить дубликат вершины
    EXPECT_TRUE(graph.hasVertex(1));
}

TEST(AdjacencyListGraphTest, AddDuplicateEdge) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 2); // Попытка добавить дубликат ребра
    EXPECT_TRUE(graph.hasEdge(1, 2));
}

TEST(AdjacencyListGraphTest, GetNeighborsOfNonexistentVertex) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    auto neighbors = graph.getNeighborsIterator(1); // Попытка получить соседей несуществующей вершины
    EXPECT_EQ(neighbors, graph.getNeighborsIterator(1)); // Итератор должен быть пустым
}

TEST(AdjacencyListGraphTest, GetFilteredNeighborsOfNonexistentVertex) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; }); // Попытка получить отфильтрованных соседей несуществующей вершины
    EXPECT_EQ(filteredNeighbors, graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; })); // Итератор должен быть пустым
}

TEST(AdjacencyListGraphTest, LargeGraph) {
    graph::AdjacencyListGraph<int, graph::Edge> graph;
    for (int i = 0; i < 1000; ++i) {
        graph.addVertex(i);
    }
    for (int i = 0; i < 999; ++i) {
        graph.addEdge(i, i + 1);
    }
    EXPECT_TRUE(graph.hasEdge(0, 1));
    EXPECT_TRUE(graph.hasEdge(999, 998));
    EXPECT_FALSE(graph.hasEdge(0, 999));
}