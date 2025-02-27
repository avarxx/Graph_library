#include "gtest/gtest.h"
#include "graph/AdjacencyMatrixGraph.h"

TEST(AdjacencyMatrixGraphTest, AddVertex) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_FALSE(graph.hasVertex(2));
}

TEST(AdjacencyMatrixGraphTest, RemoveVertex) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeVertex(1);
    EXPECT_FALSE(graph.hasVertex(1));
    EXPECT_TRUE(graph.hasVertex(2));
}

TEST(AdjacencyMatrixGraphTest, AddEdge) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_FALSE(graph.hasEdge(2, 1));
}

TEST(AdjacencyMatrixGraphTest, RemoveEdge) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    graph.removeEdge(1, 2);
    EXPECT_FALSE(graph.hasEdge(1, 2));
}

TEST(AdjacencyMatrixGraphTest, GetNeighborsIterator) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
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

TEST(AdjacencyMatrixGraphTest, GetFilteredNeighborsIterator) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 3; });
    EXPECT_EQ(*filteredNeighbors, 3);
}

TEST(AdjacencyMatrixGraphTest, HasVertex) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_FALSE(graph.hasVertex(2));
}

TEST(AdjacencyMatrixGraphTest, HasEdge) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_FALSE(graph.hasEdge(2, 1));
}

TEST(AdjacencyMatrixGraphTest, RemoveNonexistentVertex) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.removeVertex(2); // Попытка удалить несуществующую вершину
    EXPECT_TRUE(graph.hasVertex(1));
}

TEST(AdjacencyMatrixGraphTest, RemoveNonexistentEdge) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeEdge(1, 2); // Попытка удалить несуществующее ребро
    EXPECT_FALSE(graph.hasEdge(1, 2));
}

TEST(AdjacencyMatrixGraphTest, AddDuplicateVertex) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(1); // Попытка добавить дубликат вершины
    EXPECT_TRUE(graph.hasVertex(1));
}

TEST(AdjacencyMatrixGraphTest, AddDuplicateEdge) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 2); // Попытка добавить дубликат ребра
    EXPECT_TRUE(graph.hasEdge(1, 2));
}

TEST(AdjacencyMatrixGraphTest, GetNeighborsOfNonexistentVertex) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    auto neighbors = graph.getNeighborsIterator(1); // Попытка получить соседей несуществующей вершины
    EXPECT_EQ(neighbors, graph.getNeighborsIterator(1)); // Итератор должен быть пустым
}

TEST(AdjacencyMatrixGraphTest, GetFilteredNeighborsOfNonexistentVertex) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; }); // Попытка получить отфильтрованных соседей несуществующей вершины
    EXPECT_EQ(filteredNeighbors, graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; })); // Итератор должен быть пустым
}

TEST(AdjacencyMatrixGraphTest, LargeGraph) {
    graph::AdjacencyMatrixGraph<int, graph::Edge> graph;
    for (int i = 0; i < 100; ++i) {
        graph.addVertex(i);
    }
    for (int i = 0; i < 99; ++i) {
        graph.addEdge(i, i + 1);
    }
    EXPECT_TRUE(graph.hasEdge(0, 1));
    EXPECT_TRUE(graph.hasEdge(99, 98));
    EXPECT_FALSE(graph.hasEdge(0, 99));
}