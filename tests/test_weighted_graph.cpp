// #include "gtest/gtest.h"
// // #include "../include/graph/EdgeListGraph.h"
// #include "../include/graph/WeightedGraph.h"

// TEST(WeightedGraphTest, AddVertex) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
//     EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
// }

// TEST(WeightedGraphTest, RemoveVertex) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(2));
//     graph.removeVertex(graph::Vertex(1));
//     EXPECT_FALSE(graph.hasVertex(graph::Vertex(1)));
//     EXPECT_TRUE(graph.hasVertex(graph::Vertex(2)));
// }

// TEST(WeightedGraphTest, AddEdge) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(2));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(2), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(2), 10));
//     EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
//     //EXPECT_EQ(graph.getEdgeWeight(graph::Vertex(1), graph::Vertex(2)), 10);
// }

// TEST(WeightedGraphTest, RemoveEdge) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(2));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(2), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(2), 10));
//     graph.removeEdge(graph::Vertex(1), graph::Vertex(2));
//     EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
// }

// TEST(WeightedGraphTest, GetNeighborsIterator) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(2));
//     graph.addVertex(graph::Vertex(3));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(2), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(2), 10));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(3), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(3), 20));
//     auto neighbors = graph.getNeighborsIterator(graph::Vertex(1));
//     EXPECT_EQ(*neighbors, graph::Vertex(2));
//     ++neighbors;
//     //EXPECT_EQ(*neighbors, 3);
// }

// TEST(WeightedGraphTest, GetFilteredNeighborsIterator) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(2));
//     graph.addVertex(graph::Vertex(3));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(2), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(2), 10));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(3), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(3), 20));
//     auto filteredNeighbors = graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(3); });
//     //EXPECT_EQ(*filteredNeighbors, 3);
// }

// TEST(WeightedGraphTest, HasVertex) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
//     EXPECT_FALSE(graph.hasVertex(graph::Vertex(2)));
// }

// TEST(WeightedGraphTest, HasEdge) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(2));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(2), 10));
//     EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
//     EXPECT_FALSE(graph.hasEdge(graph::Vertex(2), graph::Vertex(1)));
// }

// TEST(WeightedGraphTest, RemoveNonexistentVertex) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.removeVertex(graph::Vertex(2)); // Попытка удалить несуществующую вершину
//     EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
// }

// TEST(WeightedGraphTest, RemoveNonexistentEdge) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(2));
//     graph.removeEdge(graph::Vertex(1), graph::Vertex(2)); // Попытка удалить несуществующее ребро
//     EXPECT_FALSE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
// }

// TEST(WeightedGraphTest, AddDuplicateVertex) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(1)); // Попытка добавить дубликат вершины
//     EXPECT_TRUE(graph.hasVertex(graph::Vertex(1)));
// }

// TEST(WeightedGraphTest, AddDuplicateEdge) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     graph.addVertex(graph::Vertex(1));
//     graph.addVertex(graph::Vertex(2));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(2), 10));
//     graph.addEdge(graph::Vertex(1), graph::Vertex(), graph::WeightedEdge<int>(graph::Vertex(1), graph::Vertex(2), 20)); // Попытка добавить дубликат ребра
//     EXPECT_TRUE(graph.hasEdge(graph::Vertex(1), graph::Vertex(2)));
//     //EXPECT_EQ(graph.getEdgeWeight(graph::Vertex(1), graph::Vertex(2)), 20); // Вес должен обновиться
// }

// TEST(WeightedGraphTest, GetNeighborsOfNonexistentVertex) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     auto neighbors = graph.getNeighborsIterator(graph::Vertex(1)); // Попытка получить соседей несуществующей вершины
//     EXPECT_EQ(neighbors, graph.getNeighborsIterator(graph::Vertex(1))); // Итератор должен быть пустым
// }

// TEST(WeightedGraphTest, GetFilteredNeighborsOfNonexistentVertex) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     auto filteredNeighbors = graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(2); }); // Попытка получить отфильтрованных соседей несуществующей вершины
//     EXPECT_EQ(filteredNeighbors, graph.getFilteredNeighborsIterator(graph::Vertex(1), [](graph::Vertex v) { return v == graph::Vertex(2); })); // Итератор должен быть пустым
// }

// TEST(WeightedGraphTest, LargeGraph) {
//     graph::WeightedGraph<graph::Vertex, graph::WeightedEdge<int>> graph;
//     for (int i = 0; i < 100; ++i) {
//         graph.addVertex(graph::Vertex(i));
//     }
//     for (int i = 0; i < 99; ++i) {
//         graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1), graph::WeightedEdge<int>(graph::Vertex(i), graph::Vertex(i + 1), i * 10));
//     }
//     EXPECT_TRUE(graph.hasEdge(graph::Vertex(0), graph::Vertex(1)));
//     //EXPECT_EQ(graph.getEdgeWeight(graph::Vertex(0), graph::Vertex(1)), 0);
//     EXPECT_TRUE(graph.hasEdge(graph::Vertex(99), graph::Vertex(98)));
//     //EXPECT_EQ(graph.getEdgeWeight(graph::Vertex(99), graph::Vertex(98)), 980);
//     EXPECT_FALSE(graph.hasEdge(graph::Vertex(0), graph::Vertex(99)));
// }