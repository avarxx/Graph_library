add_executable(test_graph test_graph.cpp)

target_link_libraries(test_graph GraphLibrary gtest gtest_main)

add_test(NAME test_graph COMMAND test_graph)