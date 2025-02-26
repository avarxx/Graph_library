cmake_minimum_required(VERSION 3.14)
project(GraphLibrary)

# Устанавливаем стандарт C++ (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Добавляем исходные файлы проекта
add_library(GraphLibrary
  src/graph/Graph.cpp
  src/graph/AdjacencyListGraph.cpp
)

# Указываем, где искать заголовочные файлы
target_include_directories(GraphLibrary PUBLIC include)

# Добавляем поддиректорию с тестами
add_subdirectory(tests)