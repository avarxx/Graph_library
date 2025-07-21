# Находим GoogleTest
find_package(GTest REQUIRED)

# Создаем исполняемый файл для тестов
file(GLOB TEST_FILES "*.cpp")
list(REMOVE_ITEM TEST_FILES test_weighted_graph.cpp)
add_executable(GraphTests ${TEST_FILES})

# Связываем тесты с библиотекой и GoogleTest
target_link_libraries(GraphTests PRIVATE GraphLibrary GTest::GTest GTest::Main)

include(GoogleTest)
gtest_discover_tests(GraphTests)