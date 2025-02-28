#include "gtest/gtest.h"
#include "../include/graph/AdjacencyListGraph.h"
#include <iostream>

TEST(AdjacencyListGraphTest, AddVertex) {
  graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(graph::Vertex(1)));
  EXPECT_TRUE(graph.hasVertex(graph::Vertex(graph::Vertex(1))));
  EXPECT_FALSE(graph.hasVertex(graph::Vertex(graph::Vertex(2))));
}

TEST(AdjacencyListGraphTest, RemoveVertex) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(graph::Vertex(1)));
    graph.addVertex(graph::Vertex(2));
    graph.removeVertex(graph::Vertex(1));
    EXPECT_FALSE(graph.hasVertex(graph::Vertex(1)));
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(2)));
}

TEST(AdjacencyListGraphTest, AddEdge) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(AdjacencyListGraphTest, RemoveEdge) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.removeEdge(graph::Vertex(1), graph::Vertex(2));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(AdjacencyListGraphTest, GetNeighborsIterator) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addVertex(graph::Vertex(3));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(3));
    auto neighbors = graph.getNeighborsIterator(graph::Vertex(1));
    EXPECT_EQ(*neighbors, graph::Vertex(2));
    ++neighbors;
    EXPECT_EQ(*neighbors, graph::Vertex(3));
}

TEST(AdjacencyListGraphTest, GetFilteredNeighborsIterator) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addVertex(graph::Vertex(3));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(3));
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(3); });
    GTEST_LOG_(INFO) << (*filteredNeighbors).id;
    EXPECT_EQ(*filteredNeighbors, graph::Vertex(3));
}

TEST(AdjacencyListGraphTest, HasVertex) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
    EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(AdjacencyListGraphTest, HasEdge) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(AdjacencyListGraphTest, RemoveNonexistentVertex) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.removeVertex(graph::Vertex(2)); // Попытка удалить несуществующую вершину
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(AdjacencyListGraphTest, RemoveNonexistentEdge) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.removeEdge(graph::Vertex(1), graph::Vertex(2)); // Попытка удалить несуществующее ребро
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(AdjacencyListGraphTest, AddDuplicateVertex) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(1)); // Попытка добавить дубликат вершины
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(AdjacencyListGraphTest, AddDuplicateEdge) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2)); // Попытка добавить дубликат ребра
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(AdjacencyListGraphTest, GetNeighborsOfNonexistentVertex) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    auto neighbors = graph.getNeighborsIterator(graph::Vertex(1)); // Попытка получить соседей несуществующей вершины
    EXPECT_EQ(neighbors, graph.getNeighborsIterator(graph::Vertex(1))); // Итератор должен быть пустым
}

TEST(AdjacencyListGraphTest, GetFilteredNeighborsOfNonexistentVertex) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(2); }); // Попытка получить отфильтрованных соседей несуществующей вершины
    EXPECT_EQ(filteredNeighbors, graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(2); })); // Итератор должен быть пустым
}

TEST(AdjacencyListGraphTest, LargeGraph) {
    graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
    for (int i = 0; i < 1000; ++i) {
        graph.addVertex(graph::Vertex(i));
    }
    for (int i = 0; i < 999; ++i) {
        graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1));
    }
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(0), graph::Vertex(1)));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(999), graph::Vertex(998)));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(0), graph::Vertex(999)));
}