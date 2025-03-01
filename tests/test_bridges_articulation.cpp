#include "../include/algorithms/BridgesAndArticulationPoints.h"
#include "../include/graph/AdjacencyListGraph.h"
#include "../include/graph/AdjacencyMatrixGraph.h"
#include "../include/graph/DirectedGraph.h"
#include "../include/graph/EdgeListGraph.h"
#include "../include/graph/UndirectedGraph.h"
#include "../include/graph/WeightedGraph.h"
#include "gtest/gtest.h"

TEST(BAP_TEST, AdjacencyListContains) {
  graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addVertex(graph::Vertex(6));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(3), graph::Vertex(4));
  graph.addEdge(graph::Vertex(3), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(5));
  graph.addEdge(graph::Vertex(5), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(4), graph::Vertex(3));
  graph.addEdge(graph::Vertex(6), graph::Vertex(3));
  graph.addEdge(graph::Vertex(5), graph::Vertex(2));
  graph.addEdge(graph::Vertex(6), graph::Vertex(5));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(3), graph::Vertex(4)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());

  EXPECT_NE(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_NE(std::find(points.begin(), points.end(), 3), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 4), points.end());
}

TEST(BAP_TEST, AdjacencyListCycle) {
  graph::AdjacencyListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(3), graph::Vertex(1));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(3)))),
            bridges.end());

  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 3), points.end());
}

TEST(BAP_TEST, AdjacencyMatrixContains) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addVertex(graph::Vertex(6));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(3), graph::Vertex(4));
  graph.addEdge(graph::Vertex(3), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(5));
  graph.addEdge(graph::Vertex(5), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(4), graph::Vertex(3));
  graph.addEdge(graph::Vertex(6), graph::Vertex(3));
  graph.addEdge(graph::Vertex(5), graph::Vertex(2));
  graph.addEdge(graph::Vertex(6), graph::Vertex(5));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(3), graph::Vertex(4)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());

  EXPECT_NE(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_NE(std::find(points.begin(), points.end(), 3), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 4), points.end());
}

TEST(BAP_TEST, AdjacencyMatrixCycle) {
  graph::AdjacencyMatrixGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(3), graph::Vertex(1));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(3)))),
            bridges.end());

  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 3), points.end());
}

TEST(BAP_TEST, DirectedGraphContains) {
  graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addVertex(graph::Vertex(6));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(3), graph::Vertex(4));
  graph.addEdge(graph::Vertex(3), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(5));
  graph.addEdge(graph::Vertex(5), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(4), graph::Vertex(3));
  graph.addEdge(graph::Vertex(6), graph::Vertex(3));
  graph.addEdge(graph::Vertex(5), graph::Vertex(2));
  graph.addEdge(graph::Vertex(6), graph::Vertex(5));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(3), graph::Vertex(4)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());

  EXPECT_NE(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_NE(std::find(points.begin(), points.end(), 3), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 4), points.end());
}

TEST(BAP_TEST, DirectedGraphCycle) {
  graph::DirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(3), graph::Vertex(1));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(3)))),
            bridges.end());

  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 3), points.end());
}

TEST(BAP_TEST, EdgeListContains) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addVertex(graph::Vertex(6));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(3), graph::Vertex(4));
  graph.addEdge(graph::Vertex(3), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(5));
  graph.addEdge(graph::Vertex(5), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(4), graph::Vertex(3));
  graph.addEdge(graph::Vertex(6), graph::Vertex(3));
  graph.addEdge(graph::Vertex(5), graph::Vertex(2));
  graph.addEdge(graph::Vertex(6), graph::Vertex(5));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(3), graph::Vertex(4)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());

  EXPECT_NE(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_NE(std::find(points.begin(), points.end(), 3), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 4), points.end());
}

TEST(BAP_TEST, EdgeListCycle) {
  graph::EdgeListGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(3), graph::Vertex(1));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(3)))),
            bridges.end());

  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 3), points.end());
}

TEST(BAP_TEST, UndirectedContains) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));
  graph.addVertex(graph::Vertex(4));
  graph.addVertex(graph::Vertex(5));
  graph.addVertex(graph::Vertex(6));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(3), graph::Vertex(4));
  graph.addEdge(graph::Vertex(3), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(5));
  graph.addEdge(graph::Vertex(5), graph::Vertex(6));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(4), graph::Vertex(3));
  graph.addEdge(graph::Vertex(6), graph::Vertex(3));
  graph.addEdge(graph::Vertex(5), graph::Vertex(2));
  graph.addEdge(graph::Vertex(6), graph::Vertex(5));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_NE(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(3), graph::Vertex(4)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());

  EXPECT_NE(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_NE(std::find(points.begin(), points.end(), 3), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 4), points.end());
}

TEST(BAP_TEST, UndirectedCycle) {
  graph::UndirectedGraph<graph::Vertex, graph::Edge> graph;
  graph.addVertex(graph::Vertex(1));
  graph.addVertex(graph::Vertex(2));
  graph.addVertex(graph::Vertex(3));

  graph.addEdge(graph::Vertex(1), graph::Vertex(2));
  graph.addEdge(graph::Vertex(1), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(3));
  graph.addEdge(graph::Vertex(2), graph::Vertex(1));
  graph.addEdge(graph::Vertex(3), graph::Vertex(2));
  graph.addEdge(graph::Vertex(3), graph::Vertex(1));

  graph::BridgesAndArticulationPoints<graph::Vertex, graph::Edge> bap{graph};

  auto bridges = bap.findBridges();

  auto points = bap.findArticulationPoints();

  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(2)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(2), graph::Vertex(3)))),
            bridges.end());
  EXPECT_EQ(std::find(bridges.begin(), bridges.end(),
                      (graph::Edge(graph::Vertex(1), graph::Vertex(3)))),
            bridges.end());

  EXPECT_EQ(std::find(points.begin(), points.end(), 1), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 2), points.end());
  EXPECT_EQ(std::find(points.begin(), points.end(), 3), points.end());
}
