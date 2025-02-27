#include "gtest/gtest.h"
// #include "../include/graph/EdgeListGraph.h"
#include "graph/WeightedGraph.h"

TEST(WeightedGraphTest, AddVertex) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_FALSE(graph.hasVertex(2));
}

TEST(WeightedGraphTest, RemoveVertex) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeVertex(1);
    EXPECT_FALSE(graph.hasVertex(1));
    EXPECT_TRUE(graph.hasVertex(2));
}

TEST(WeightedGraphTest, AddEdge) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 10);
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_EQ(graph.getEdgeWeight(1, 2), 10);
}

TEST(WeightedGraphTest, RemoveEdge) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 10);
    graph.removeEdge(1, 2);
    EXPECT_FALSE(graph.hasEdge(1, 2));
}

TEST(WeightedGraphTest, GetNeighborsIterator) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 20);
    auto neighbors = graph.getNeighborsIterator(1);
    EXPECT_EQ(*neighbors, 2);
    ++neighbors;
    EXPECT_EQ(*neighbors, 3);
}

TEST(WeightedGraphTest, GetFilteredNeighborsIterator) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 20);
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 3; });
    EXPECT_EQ(*filteredNeighbors, 3);
}

TEST(WeightedGraphTest, HasVertex) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_FALSE(graph.hasVertex(2));
}

TEST(WeightedGraphTest, HasEdge) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 10);
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_FALSE(graph.hasEdge(2, 1));
}

TEST(WeightedGraphTest, RemoveNonexistentVertex) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.removeVertex(2); // Попытка удалить несуществующую вершину
    EXPECT_TRUE(graph.hasVertex(1));
}

TEST(WeightedGraphTest, RemoveNonexistentEdge) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeEdge(1, 2); // Попытка удалить несуществующее ребро
    EXPECT_FALSE(graph.hasEdge(1, 2));
}

TEST(WeightedGraphTest, AddDuplicateVertex) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(1); // Попытка добавить дубликат вершины
    EXPECT_TRUE(graph.hasVertex(1));
}

TEST(WeightedGraphTest, AddDuplicateEdge) {
    graph::WeightedGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 2, 20); // Попытка добавить дубликат ребра
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_EQ(graph.getEdgeWeight(1, 2), 20); // Вес должен обновиться
}

TEST(WeightedGraphTest, GetNeighborsOfNonexistentVertex) {
    graph::WeightedGraph<int, int> graph;
    auto neighbors = graph.getNeighborsIterator(1); // Попытка получить соседей несуществующей вершины
    EXPECT_EQ(neighbors, graph.getNeighborsIterator(1)); // Итератор должен быть пустым
}

TEST(WeightedGraphTest, GetFilteredNeighborsOfNonexistentVertex) {
    graph::WeightedGraph<int, int> graph;
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; }); // Попытка получить отфильтрованных соседей несуществующей вершины
    EXPECT_EQ(filteredNeighbors, graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; })); // Итератор должен быть пустым
}

TEST(WeightedGraphTest, LargeGraph) {
    graph::WeightedGraph<int, int> graph;
    for (int i = 0; i < 100; ++i) {
        graph.addVertex(i);
    }
    for (int i = 0; i < 99; ++i) {
        graph.addEdge(i, i + 1, i * 10);
    }
    EXPECT_TRUE(graph.hasEdge(0, 1));
    EXPECT_EQ(graph.getEdgeWeight(0, 1), 0);
    EXPECT_TRUE(graph.hasEdge(99, 98));
    EXPECT_EQ(graph.getEdgeWeight(99, 98), 980);
    EXPECT_FALSE(graph.hasEdge(0, 99));
}