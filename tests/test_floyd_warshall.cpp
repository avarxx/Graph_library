#include "../include/algorithms/FloydWarshall.h"
#include "../include/graph/WeightedGraph.h"
#include "gtest/gtest.h"



TEST(FloydWarshallTest, SingleNodeGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));

  auto distances = graph::FloydWarshall(graph);
  EXPECT_EQ(distances[0][0], 0);
}

TEST(FloydWarshallTest, ZeroWeightEdges) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 0);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 0);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), 0);

  auto distances = graph::FloydWarshall(graph);
  EXPECT_EQ(distances[0][0], 0);
  EXPECT_EQ(distances[0][1], 0);
  EXPECT_EQ(distances[0][2], 0);
  EXPECT_EQ(distances[1][2], 0);
}

TEST(FloydWarshallTest, LargeGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  for (int i = 0; i < 10; ++i) {
      graph.addVertex(graph::Vertex(i));
  }
  for (int i = 0; i < 9; ++i) {
      graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1), 1);
  }

  auto distances = graph::FloydWarshall(graph);
  for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
          if (i == j) {
              EXPECT_EQ(distances[i][j], 0);
          } else if (j > i) {
              EXPECT_EQ(distances[i][j], j - i);
          } else {
              EXPECT_EQ(distances[i][j], std::numeric_limits<int>::max());
          }
      }
  }
}

TEST(FloydWarshallTest, NegativeWeightsNoCycle) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), -1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), -2);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), -3);

  auto distances = graph::FloydWarshall(graph);
  EXPECT_EQ(distances[0][0], 0);
  EXPECT_EQ(distances[0][1], -1);
  EXPECT_EQ(distances[0][2], -3);
  EXPECT_EQ(distances[1][2], -2);
}

TEST(FloydWarshallTest, AllPairsDisconnected) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  for (int i = 0; i < 5; ++i) {
      graph.addVertex(graph::Vertex(i));
  }

  auto distances = graph::FloydWarshall(graph);
  for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
          if (i == j) {
              EXPECT_EQ(distances[i][j], 0);
          } else {
              EXPECT_EQ(distances[i][j], std::numeric_limits<int>::max());
          }
      }
  }
}

TEST(FloydWarshallTest, MixedWeights) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), -1);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), 3);

  auto distances = graph::FloydWarshall(graph);
  EXPECT_EQ(distances[0][0], 0);
  EXPECT_EQ(distances[0][1], 1);
  EXPECT_EQ(distances[0][2], 0);  
  EXPECT_EQ(distances[1][2], -1);
}

TEST(FloydWarshallTest, LargeNegativeWeights) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), -100);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), -200);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), -250);

  auto distances = graph::FloydWarshall(graph);
  EXPECT_EQ(distances[0][0], 0);
  EXPECT_EQ(distances[0][1], -100);
  EXPECT_EQ(distances[0][2], -300);  
  EXPECT_EQ(distances[1][2], -200);
}

TEST(FloydWarshallTest, MultiplePaths) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 2);
  graph.addEdge(graph::Vertex(0), graph::Vertex(2), 4);
  graph.addEdge(graph::Vertex(1), graph::Vertex(0), 1);

  auto distances = graph::FloydWarshall(graph);
  EXPECT_EQ(distances[0][0], 0);
  EXPECT_EQ(distances[0][1], 1);
  EXPECT_EQ(distances[0][2], 3);  
  EXPECT_EQ(distances[1][2], 2);
  EXPECT_EQ(distances[1][0], 1);
}

TEST(FloydWarshallTest, NoEdges) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));

  auto distances = graph::FloydWarshall(graph);
  EXPECT_EQ(distances[0][0], 0);
  EXPECT_EQ(distances[0][1], std::numeric_limits<int>::max());
  EXPECT_EQ(distances[0][2], std::numeric_limits<int>::max());
  EXPECT_EQ(distances[1][2], std::numeric_limits<int>::max());
}

TEST(FloydWarshallTest, LargeGraphWithNegativeWeights) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  for (int i = 0; i < 10; ++i) {
      graph.addVertex(graph::Vertex(i));
  }
  for (int i = 0; i < 9; ++i) {
      graph.addEdge(graph::Vertex(i), graph::Vertex(i + 1), -1);
  }

  auto distances = graph::FloydWarshall(graph);
  for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
          if (i == j) {
              EXPECT_EQ(distances[i][j], 0);
          } else if (j > i) {
              EXPECT_EQ(distances[i][j], -(j - i));
          } else {
              EXPECT_EQ(distances[i][j], std::numeric_limits<int>::max());
          }
      }
  }
}

TEST(FloydWarshallTest, ComplexGraph) {
  graph::WeightedGraph<graph::Vertex, int> graph;
  graph.addVertex(graph::Vertex(0));
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addEdge(graph::Vertex(0), graph::Vertex(1), 1);
  graph.addEdge(graph::Vertex(1), graph::Vertex(2), 2);
  graph.addEdge(graph::Vertex(2), graph::Vertex(3), 3);
  graph.addEdge(graph::Vertex(0), graph::Vertex(3), 10);

  auto distances = graph::FloydWarshall(graph);
  EXPECT_EQ(distances[0][0], 0);
  EXPECT_EQ(distances[0][1], 1);
  EXPECT_EQ(distances[0][2], 3);
  EXPECT_EQ(distances[0][3], 6); 
  EXPECT_EQ(distances[1][3], 5);
}