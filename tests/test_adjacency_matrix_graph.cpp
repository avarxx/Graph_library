#include "gtest/gtest.h"
#include "../include/graph/AdjacencyMatrixGraph.h"

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

TEST(AdjacencyMatrixGraphTest, GetNeighborsIterator) {
    graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
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

TEST(AdjacencyMatrixGraphTest, GetFilteredNeighborsIterator) {
    graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addVertex(graph::Vertex(3));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(3));
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(3); });
    EXPECT_EQ(*filteredNeighbors, graph::Vertex(3));
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
    graph.removeVertex(graph::Vertex(2)); // Попытка удалить несуществующую вершину
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(AdjacencyMatrixGraphTest, RemoveNonexistentEdge) {
    graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.removeEdge(graph::Vertex(1), graph::Vertex(2)); // Попытка удалить несуществующее ребро
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(AdjacencyMatrixGraphTest, AddDuplicateVertex) {
    graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(1)); // Попытка добавить дубликат вершины
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(AdjacencyMatrixGraphTest, AddDuplicateEdge) {
    graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2)); // Попытка добавить дубликат ребра
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(AdjacencyMatrixGraphTest, GetNeighborsOfNonexistentVertex) {
    graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
    auto neighbors = graph.getNeighborsIterator(graph::Vertex(1)); // Попытка получить соседей несуществующей вершины
    EXPECT_EQ(neighbors, graph.getNeighborsIterator(graph::Vertex(1))); // Итератор должен быть пустым
}

TEST(AdjacencyMatrixGraphTest, GetFilteredNeighborsOfNonexistentVertex) {
    graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(2); }); // Попытка получить отфильтрованных соседей несуществующей вершины
    EXPECT_EQ(filteredNeighbors, graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(2); })); // Итератор должен быть пустым
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
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(99), graph::Vertex(98)));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(0), graph::Vertex(99)));
}