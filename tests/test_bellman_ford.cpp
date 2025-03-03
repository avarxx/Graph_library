#include "../include/algorithms/find_distance/BellmanFord.h"
#include "../include/graph/WeightedGraph.h"
#include "gtest/gtest.h"

TEST(BellmanFordTest, SimpleGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 2);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), 4);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], 1);
  EXPECT_EQ(distances[graph::Vertex(2)], 3);
}

TEST(BellmanFordTest, DisconnectedGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], 1);
  EXPECT_EQ(distances[graph::Vertex(2)], std::numeric_limits<int>::max());
}

TEST(BellmanFordTest, NegativeWeights) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), -1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), -2);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], -1);
  EXPECT_EQ(distances[graph::Vertex(2)], -3);
}

TEST(BellmanFordTest, SingleVertexGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
}

TEST(BellmanFordTest, NegativeCycle) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), -2);
  graph.addEdge(graph::Vertex(2), graph::Vertex(0), -1);

  EXPECT_THROW(graph::BellmanFord(graph, graph::Vertex(0)), std::runtime_error);
}

TEST(BellmanFordTest, LargeGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  for (int i = 0; i < 10; ++i) {
    graph.addVertex(graph::Vertex(i));
  }
  for (int i = 0; i < 9; ++i) {
    graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1), 1);
  }

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(distances[graph::Vertex(i)], i);
  }
}

TEST(BellmanFordTest, MultiplePaths) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 2);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), 4);
  graph.addEdge(graph::Vertex(2), graph::Vertex(3), 1);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], 1);
  EXPECT_EQ(distances[graph::Vertex(2)], 3);
  EXPECT_EQ(distances[graph::Vertex(3)], 4);
}

TEST(BellmanFordTest, ZeroWeightEdges) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 0);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 0);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], 0);
  EXPECT_EQ(distances[graph::Vertex(2)], 0);
}

TEST(BellmanFordTest, MixedWeights) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), -1);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), 3);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], 1);
  EXPECT_EQ(distances[graph::Vertex(2)], 0);
}

TEST(BellmanFordTest, NoEdges) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], std::numeric_limits<int>::max());
  EXPECT_EQ(distances[graph::Vertex(2)], std::numeric_limits<int>::max());
}

TEST(BellmanFordTest, SelfLoops) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addEdge(graph::Vertex(0), graph::Vertex(0), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(1), -1);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], std::numeric_limits<int>::max());
}

TEST(BellmanFordTest, MultipleNegativeEdges) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), -1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), -2);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), -3);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], -1);
  EXPECT_EQ(distances[graph::Vertex(2)], -3);
}

TEST(BellmanFordTest, ComplexGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 2);
  graph.addEdge(graph::Vertex(2), graph::Vertex(3), 3);
  graph.addEdge(graph::Vertex(0), graph::Vertex(3), 10);

  auto distances = graph::BellmanFord(graph, graph::Vertex(0));
  EXPECT_EQ(distances[graph::Vertex(0)], 0);
  EXPECT_EQ(distances[graph::Vertex(1)], 1);
  EXPECT_EQ(distances[graph::Vertex(2)], 3);
  EXPECT_EQ(distances[graph::Vertex(3)], 6);
}

TEST(BellmanFordTest, LargeNegativeCycle) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  for (int i = 0; i < 5; ++i) {
    graph.addVertex(graph::Vertex(i));
  }
  for (int i = 0; i < 4; ++i) {
    graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1), -1);
  }
  graph.addEdge(graph::Vertex(4), graph::Vertex(0), -1);

  EXPECT_THROW(graph::BellmanFord(graph, graph::Vertex(0)), std::runtime_error);
}