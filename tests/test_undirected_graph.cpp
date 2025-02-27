#include "gtest/gtest.h"
#include "graph/UndirectedGraph.h"

TEST(UndirectedGraphTest, AddVertex) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_FALSE(graph.hasVertex(2));
}

TEST(UndirectedGraphTest, RemoveVertex) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeVertex(1);
    EXPECT_FALSE(graph.hasVertex(1));
    EXPECT_TRUE(graph.hasVertex(2));
}

TEST(UndirectedGraphTest, AddEdge) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_TRUE(graph.hasEdge(2, 1)); // В неориентированном графе ребро двунаправленное
}

TEST(UndirectedGraphTest, RemoveEdge) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    graph.removeEdge(1, 2);
    EXPECT_FALSE(graph.hasEdge(1, 2));
    EXPECT_FALSE(graph.hasEdge(2, 1)); // В неориентированном графе удаляется оба направления
}

TEST(UndirectedGraphTest, GetNeighborsIterator) {
    graph::UndirectedGraph<int, graph::Edge> graph;
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

TEST(UndirectedGraphTest, GetFilteredNeighborsIterator) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 3; });
    EXPECT_EQ(*filteredNeighbors, 3);
}

TEST(UndirectedGraphTest, HasVertex) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_FALSE(graph.hasVertex(2));
}

TEST(UndirectedGraphTest, HasEdge) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_TRUE(graph.hasEdge(2, 1)); // В неориентированном графе ребро двунаправленное
}

TEST(UndirectedGraphTest, RemoveNonexistentVertex) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.removeVertex(2); // Попытка удалить несуществующую вершину
    EXPECT_TRUE(graph.hasVertex(1));
}

TEST(UndirectedGraphTest, RemoveNonexistentEdge) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeEdge(1, 2); // Попытка удалить несуществующее ребро
    EXPECT_FALSE(graph.hasEdge(1, 2));
    EXPECT_FALSE(graph.hasEdge(2, 1)); // В неориентированном графе удаляется оба направления
}

TEST(UndirectedGraphTest, AddDuplicateVertex) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(1); // Попытка добавить дубликат вершины
    EXPECT_TRUE(graph.hasVertex(1));
}

TEST(UndirectedGraphTest, AddDuplicateEdge) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 2); // Попытка добавить дубликат ребра
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_TRUE(graph.hasEdge(2, 1)); // В неориентированном графе ребро двунаправленное
}

TEST(UndirectedGraphTest, GetNeighborsOfNonexistentVertex) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    auto neighbors = graph.getNeighborsIterator(1); // Попытка получить соседей несуществующей вершины
    EXPECT_EQ(neighbors, graph.getNeighborsIterator(1)); // Итератор должен быть пустым
}

TEST(UndirectedGraphTest, GetFilteredNeighborsOfNonexistentVertex) {
    graph::UndirectedGraph<int, graph::Edge> graph;
    auto filteredNeighbors = graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; }); // Попытка получить отфильтрованных соседей несуществующей вершины
    EXPECT_EQ(filteredNeighbors, graph.getFilteredNeighborsIterator(1, [](int v) { return v == 2; })); // Итератор должен быть пустым
}

TEST(UndirectedGraphTest, LargeGraph) {
    graph::UndirectedGraph<int, graph::Edge> graph;
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