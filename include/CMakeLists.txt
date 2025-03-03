# Указываем, что это интерфейсная библиотека (заголовки)
add_library(GraphHeaders INTERFACE)

# Добавляем путь к заголовкам
target_include_directories(GraphHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/graph)
target_include_directories(GraphHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/visitors)
target_include_directories(GraphHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/bfs_dfs)
target_include_directories(GraphHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/find_distance)