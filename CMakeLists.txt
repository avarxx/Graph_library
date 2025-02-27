cmake_minimum_required(VERSION 3.14)
project(GraphLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(AdjacencyListGraph
    src/graph/AdjacencyListGraph.cpp
    include/graph/AdjacencyListGraph.h
)
target_include_directories(AdjacencyListGraph PUBLIC include)

add_library(AdjacencyMatrixGraph
    src/graph/AdjacencyMatrixGraph.cpp
    include/graph/AdjacencyMatrixGraph.h
)
target_include_directories(AdjacencyMatrixGraph PUBLIC include)

add_library(EdgeListGraph
    src/graph/EdgeListGraph.cpp
    include/graph/EdgeListGraph.h
)
target_include_directories(EdgeListGraph PUBLIC include)

add_library(DirectedGraph
    src/graph/DirectedGraph.cpp
    include/graph/DirectedGraph.h
)
target_include_directories(DirectedGraph PUBLIC include)

add_library(UndirectedGraph
    src/graph/UndirectedGraph.cpp
    include/graph/UndirectedGraph.h
)
target_include_directories(UndirectedGraph PUBLIC include)

add_library(WeightedGraph
    src/graph/WeightedGraph.cpp
    include/graph/WeightedGraph.h
)
target_include_directories(WeightedGraph PUBLIC include)

add_subdirectory(tests)