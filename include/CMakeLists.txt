# Указываем, что это интерфейсная библиотека (заголовки)
add_library(GraphHeaders INTERFACE)

# Добавляем путь к заголовкам
target_include_directories(GraphHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/graph)