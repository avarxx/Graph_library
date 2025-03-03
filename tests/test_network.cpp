// #include "../include/algorithms/flowNetwork/EdmondsKarp.h"
// #include "../include/algorithms/flowNetwork/FordFulkerson.h"
// #include "../include/algorithms/flowNetwork/Dinic.h"
// #include "../include/algorithms/flowNetwork/FlowNetwork.h"
// #include "../include/graph/AdjacencyListGraph.h"
// #include "../include/graph/DirectedGraph.h"
// #include "../include/graph/WeightedGraph.h"
// #include "gtest/gtest.h"
// #include <climits>

// using namespace graph;

// WeightedGraph<Vertex, Edge> createBaseFlowGraph() {
//   WeightedGraph<Vertex, Edge> graph;

//   graph.addVertex(Vertex(1));  // source
//   graph.addVertex(Vertex(2));
//   graph.addVertex(Vertex(3));
//   graph.addVertex(Vertex(4));  // sink

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 10));
//   graph.addEdge(Vertex(1), Vertex(3), Edge(Vertex(1), Vertex(3), 10));
//   graph.addEdge(Vertex(2), Vertex(3), Edge(Vertex(2), Vertex(3), 2));
//   graph.addEdge(Vertex(2), Vertex(4), Edge(Vertex(2), Vertex(4), 8));
//   graph.addEdge(Vertex(3), Vertex(4), Edge(Vertex(3), Vertex(4), 10));

//   return graph;
// }

// // Тесты для алгоритма Ford-Fulkerson
// TEST(FORD_FULKERSON_TEST, SimpleGraph) {
//   auto graph = createBaseFlowGraph();
//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   FordFulkerson<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(4));
//   EXPECT_EQ(maxFlow, 18);
// }

// TEST(FORD_FULKERSON_TEST, SinglePath) {
//   WeightedGraph<Vertex, Edge> graph;

//   graph.addVertex(Vertex(1));
//   graph.addVertex(Vertex(2));
//   graph.addVertex(Vertex(3));

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 5));
//   graph.addEdge(Vertex(2), Vertex(3), Edge(Vertex(2), Vertex(3), 5));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   FordFulkerson<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(3));
//   EXPECT_EQ(maxFlow, 5);
// }

// TEST(FORD_FULKERSON_TEST, DiamondGraph) {
//   WeightedGraph<Vertex, Edge> graph;

//   graph.addVertex(Vertex(1));
//   graph.addVertex(Vertex(2));
//   graph.addVertex(Vertex(3));
//   graph.addVertex(Vertex(4));

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 7));
//   graph.addEdge(Vertex(1), Vertex(3), Edge(Vertex(1), Vertex(3), 4));
//   graph.addEdge(Vertex(2), Vertex(4), Edge(Vertex(2), Vertex(4), 5));
//   graph.addEdge(Vertex(3), Vertex(4), Edge(Vertex(3), Vertex(4), 8));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   FordFulkerson<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(4));
//   EXPECT_EQ(maxFlow, 11);
// }

// TEST(FORD_FULKERSON_TEST, ComplexGraph) {
//   WeightedGraph<Vertex, Edge> graph;

//   for (int i = 1; i <= 6; ++i) {
//     graph.addVertex(Vertex(i));
//   }

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 16));
//   graph.addEdge(Vertex(1), Vertex(3), Edge(Vertex(1), Vertex(3), 13));
//   graph.addEdge(Vertex(2), Vertex(3), Edge(Vertex(2), Vertex(3), 10));
//   graph.addEdge(Vertex(2), Vertex(4), Edge(Vertex(2), Vertex(4), 12));
//   graph.addEdge(Vertex(3), Vertex(2), Edge(Vertex(3), Vertex(2), 4));
//   graph.addEdge(Vertex(3), Vertex(5), Edge(Vertex(3), Vertex(5), 14));
//   graph.addEdge(Vertex(4), Vertex(3), Edge(Vertex(4), Vertex(3), 9));
//   graph.addEdge(Vertex(4), Vertex(6), Edge(Vertex(4), Vertex(6), 20));
//   graph.addEdge(Vertex(5), Vertex(4), Edge(Vertex(5), Vertex(4), 7));
//   graph.addEdge(Vertex(5), Vertex(6), Edge(Vertex(5), Vertex(6), 4));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   FordFulkerson<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(6));
//   EXPECT_EQ(maxFlow, 23);
// }

// TEST(FORD_FULKERSON_TEST, NoPath) {
//   WeightedGraph<Vertex, Edge> graph;

//   graph.addVertex(Vertex(1));
//   graph.addVertex(Vertex(2));
//   graph.addVertex(Vertex(3));
//   graph.addVertex(Vertex(4));

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 10));
//   graph.addEdge(Vertex(3), Vertex(4), Edge(Vertex(3), Vertex(4), 10));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   FordFulkerson<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(4));
//   EXPECT_EQ(maxFlow, 0);
// }

// // Тесты для алгоритма Edmonds-Karp
// TEST(EDMONDS_KARP_TEST, SimpleGraph) {
//   auto graph = createBaseFlowGraph();
//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   EdmondsKarp<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(4));
//   EXPECT_EQ(maxFlow, 18);
// }

// TEST(EDMONDS_KARP_TEST, SinglePath) {
//   WeightedGraph<Vertex, Edge> graph;

//   graph.addVertex(Vertex(1));
//   graph.addVertex(Vertex(2));
//   graph.addVertex(Vertex(3));

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 5));
//   graph.addEdge(Vertex(2), Vertex(3), Edge(Vertex(2), Vertex(3), 5));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   EdmondsKarp<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(3));
//   EXPECT_EQ(maxFlow, 5);
// }

// TEST(EDMONDS_KARP_TEST, DiamondGraph) {
//   WeightedGraph<Vertex, Edge> graph;

//   graph.addVertex(Vertex(1));
//   graph.addVertex(Vertex(2));
//   graph.addVertex(Vertex(3));
//   graph.addVertex(Vertex(4));

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 7));
//   graph.addEdge(Vertex(1), Vertex(3), Edge(Vertex(1), Vertex(3), 4));
//   graph.addEdge(Vertex(2), Vertex(4), Edge(Vertex(2), Vertex(4), 5));
//   graph.addEdge(Vertex(3), Vertex(4), Edge(Vertex(3), Vertex(4), 8));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   EdmondsKarp<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(4));
//   EXPECT_EQ(maxFlow, 11);
// }

// TEST(EDMONDS_KARP_TEST, ComplexGraph) {
//   WeightedGraph<Vertex, Edge> graph;

//   for (int i = 1; i <= 6; ++i) {
//     graph.addVertex(Vertex(i));
//   }

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 16));
//   graph.addEdge(Vertex(1), Vertex(3), Edge(Vertex(1), Vertex(3), 13));
//   graph.addEdge(Vertex(2), Vertex(3), Edge(Vertex(2), Vertex(3), 10));
//   graph.addEdge(Vertex(2), Vertex(4), Edge(Vertex(2), Vertex(4), 12));
//   graph.addEdge(Vertex(3), Vertex(2), Edge(Vertex(3), Vertex(2), 4));
//   graph.addEdge(Vertex(3), Vertex(5), Edge(Vertex(3), Vertex(5), 14));
//   graph.addEdge(Vertex(4), Vertex(3), Edge(Vertex(4), Vertex(3), 9));
//   graph.addEdge(Vertex(4), Vertex(6), Edge(Vertex(4), Vertex(6), 20));
//   graph.addEdge(Vertex(5), Vertex(4), Edge(Vertex(5), Vertex(4), 7));
//   graph.addEdge(Vertex(5), Vertex(6), Edge(Vertex(5), Vertex(6), 4));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   EdmondsKarp<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(6));
//   EXPECT_EQ(maxFlow, 23);
// }

// TEST(EDMONDS_KARP_TEST, MultipleAugmentingPaths) {
//   WeightedGraph<Vertex, Edge> graph;

//   for (int i = 1; i <= 7; ++i) {
//     graph.addVertex(Vertex(i));
//   }

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 3));
//   graph.addEdge(Vertex(1), Vertex(4), Edge(Vertex(1), Vertex(4), 3));
//   graph.addEdge(Vertex(2), Vertex(3), Edge(Vertex(2), Vertex(3), 4));
//   graph.addEdge(Vertex(3), Vertex(7), Edge(Vertex(3), Vertex(7), 2));
//   graph.addEdge(Vertex(4), Vertex(5), Edge(Vertex(4), Vertex(5), 6));
//   graph.addEdge(Vertex(4), Vertex(6), Edge(Vertex(4), Vertex(6), 2));
//   graph.addEdge(Vertex(5), Vertex(3), Edge(Vertex(5), Vertex(3), 1));
//   graph.addEdge(Vertex(5), Vertex(7), Edge(Vertex(5), Vertex(7), 1));
//   graph.addEdge(Vertex(6), Vertex(7), Edge(Vertex(6), Vertex(7), 5));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   EdmondsKarp<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(7));
//   EXPECT_EQ(maxFlow, 6);
// }

// // Тесты для алгоритма Dinic
// TEST(DINIC_TEST, SimpleGraph) {
//   auto graph = createBaseFlowGraph();
//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   DinicSolver<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(4));
//   EXPECT_EQ(maxFlow, 18);
// }

// TEST(DINIC_TEST, SinglePath) {
//   WeightedGraph<Vertex, Edge> graph;

//   graph.addVertex(Vertex(1));
//   graph.addVertex(Vertex(2));
//   graph.addVertex(Vertex(3));

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 5));
//   graph.addEdge(Vertex(2), Vertex(3), Edge(Vertex(2), Vertex(3), 5));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   DinicSolver<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(3));
//   EXPECT_EQ(maxFlow, 5);
// }

// TEST(DINIC_TEST, DiamondGraph) {
//   WeightedGraph<Vertex, Edge> graph;

//   graph.addVertex(Vertex(1));
//   graph.addVertex(Vertex(2));
//   graph.addVertex(Vertex(3));
//   graph.addVertex(Vertex(4));

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 7));
//   graph.addEdge(Vertex(1), Vertex(3), Edge(Vertex(1), Vertex(3), 4));
//   graph.addEdge(Vertex(2), Vertex(4), Edge(Vertex(2), Vertex(4), 5));
//   graph.addEdge(Vertex(3), Vertex(4), Edge(Vertex(3), Vertex(4), 8));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   DinicSolver<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(4));
//   EXPECT_EQ(maxFlow, 11);
// }

// TEST(DINIC_TEST, ComplexGraph) {
//   WeightedGraph<Vertex, Edge> graph;

//   for (int i = 1; i <= 6; ++i) {
//     graph.addVertex(Vertex(i));
//   }

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 16));
//   graph.addEdge(Vertex(1), Vertex(3), Edge(Vertex(1), Vertex(3), 13));
//   graph.addEdge(Vertex(2), Vertex(3), Edge(Vertex(2), Vertex(3), 10));
//   graph.addEdge(Vertex(2), Vertex(4), Edge(Vertex(2), Vertex(4), 12));
//   graph.addEdge(Vertex(3), Vertex(2), Edge(Vertex(3), Vertex(2), 4));
//   graph.addEdge(Vertex(3), Vertex(5), Edge(Vertex(3), Vertex(5), 14));
//   graph.addEdge(Vertex(4), Vertex(3), Edge(Vertex(4), Vertex(3), 9));
//   graph.addEdge(Vertex(4), Vertex(6), Edge(Vertex(4), Vertex(6), 20));
//   graph.addEdge(Vertex(5), Vertex(4), Edge(Vertex(5), Vertex(4), 7));
//   graph.addEdge(Vertex(5), Vertex(6), Edge(Vertex(5), Vertex(6), 4));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   DinicSolver<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(6));
//   EXPECT_EQ(maxFlow, 23);
// }

// TEST(DINIC_TEST, LargeGraph) {
//   WeightedGraph<Vertex, Edge> graph;

//   for (int i = 1; i <= 10; ++i) {
//     graph.addVertex(Vertex(i));
//   }

//   graph.addEdge(Vertex(1), Vertex(2), Edge(Vertex(1), Vertex(2), 10));
//   graph.addEdge(Vertex(1), Vertex(3), Edge(Vertex(1), Vertex(3), 10));
//   graph.addEdge(Vertex(1), Vertex(4), Edge(Vertex(1), Vertex(4), 10));

//   graph.addEdge(Vertex(2), Vertex(5), Edge(Vertex(2), Vertex(5), 8));
//   graph.addEdge(Vertex(2), Vertex(6), Edge(Vertex(2), Vertex(6), 4));
//   graph.addEdge(Vertex(3), Vertex(5), Edge(Vertex(3), Vertex(5), 5));
//   graph.addEdge(Vertex(3), Vertex(7), Edge(Vertex(3), Vertex(7), 7));
//   graph.addEdge(Vertex(4), Vertex(6), Edge(Vertex(4), Vertex(6), 6));
//   graph.addEdge(Vertex(4), Vertex(7), Edge(Vertex(4), Vertex(7), 9));

//   graph.addEdge(Vertex(5), Vertex(8), Edge(Vertex(5), Vertex(8), 10));
//   graph.addEdge(Vertex(6), Vertex(8), Edge(Vertex(6), Vertex(8), 10));
//   graph.addEdge(Vertex(7), Vertex(8), Edge(Vertex(7), Vertex(8), 10));

//   FlowNetwork<WeightedGraph<Vertex, Edge>> network(graph);
//   DinicSolver<WeightedGraph<Vertex, Edge>> solver(network);

//   int maxFlow = solver.computeMaxFlow(Vertex(1), Vertex(8));
//   EXPECT_EQ(maxFlow, 30);
// }