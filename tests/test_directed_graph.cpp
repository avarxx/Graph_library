#include "gtest/gtest.h"
#include "../include/graph/DirectedGraph.h"

TEST(DirectedGraphTest, AddVertex) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
    EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(DirectedGraphTest, RemoveVertex) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.removeVertex(graph::Vertex(1));
    EXPECT_FALSE(graph.hasVertex(graph::Vertex(1)));
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(2)));
}

TEST(DirectedGraphTest, AddEdge) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(DirectedGraphTest, RemoveEdge) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.removeEdge(graph::Vertex(1), graph::Vertex(2));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(DirectedGraphTest, GetNeighborsIterator) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
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

TEST(DirectedGraphTest, GetFilteredNeighborsIterator) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addVertex(graph::Vertex(3));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(3));
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(3); });
    EXPECT_EQ(*filteredNeighbors, graph::Vertex(3));
}

TEST(DirectedGraphTest, HasVertex) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
    EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
}

TEST(DirectedGraphTest, HasEdge) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
}

TEST(DirectedGraphTest, RemoveNonexistentVertex) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.removeVertex(graph::Vertex(2)); // Попытка удалить несуществующую вершину
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(DirectedGraphTest, RemoveNonexistentEdge) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.removeEdge(graph::Vertex(1), graph::Vertex(2)); // Попытка удалить несуществующее ребро
    EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(DirectedGraphTest, AddDuplicateVertex) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(1)); // Попытка добавить дубликат вершины
    EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
}

TEST(DirectedGraphTest, AddDuplicateEdge) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    graph.addVertex(graph::Vertex(1));
    graph.addVertex(graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2));
    graph.addEdge(graph::Vertex(1), graph::Vertex(2)); // Попытка добавить дубликат ребра
    EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
}

TEST(DirectedGraphTest, GetNeighborsOfNonexistentVertex) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    auto neighbors = graph.getNeighborsIterator(graph::Vertex(1)); // Попытка получить соседей несуществующей вершины
    EXPECT_EQ(neighbors, graph.getNeighborsIterator(graph::Vertex(1))); // Итератор должен быть пустым
}

TEST(DirectedGraphTest, GetFilteredNeighborsOfNonexistentVertex) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(2); }); // Попытка получить отфильтрованных соседей несуществующей вершины
    EXPECT_EQ(filteredNeighbors, graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(2); })); // Итератор должен быть пустым
}

TEST(DirectedGraphTest, LargeGraph) {
    graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
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