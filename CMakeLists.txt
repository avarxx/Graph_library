cmake_minimum_required(VERSION 3.10)
project(MyGraphProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

# Добавляем поддиректории
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)

# Добавляем пользовательскую цель для запуска тестов
add_custom_target(run_tests ALL
    COMMAND ctest --output-on-failure
    DEPENDS GraphTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
