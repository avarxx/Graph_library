# Создаем библиотеку из исходных файлов
file(GLOB SRC_FILES "graph/*.cpp")
add_library(GraphLibrary STATIC ${SRC_FILES})

# Связываем с заголовками
target_link_libraries(GraphLibrary PUBLIC GraphHeaders)