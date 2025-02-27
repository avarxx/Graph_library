# CMake generated Testfile for 
# Source directory: /home/anxx/prog/project_of_algoritms/Graph_library/tests
# Build directory: /home/anxx/prog/project_of_algoritms/Graph_library/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_adjacency_list_graph "/home/anxx/prog/project_of_algoritms/Graph_library/build/tests/test_adjacency_list_graph")
set_tests_properties(test_adjacency_list_graph PROPERTIES  _BACKTRACE_TRIPLES "/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;29;add_test;/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;0;")
add_test(test_adjacency_matrix_graph "/home/anxx/prog/project_of_algoritms/Graph_library/build/tests/test_adjacency_matrix_graph")
set_tests_properties(test_adjacency_matrix_graph PROPERTIES  _BACKTRACE_TRIPLES "/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;30;add_test;/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;0;")
add_test(test_edge_list_graph "/home/anxx/prog/project_of_algoritms/Graph_library/build/tests/test_edge_list_graph")
set_tests_properties(test_edge_list_graph PROPERTIES  _BACKTRACE_TRIPLES "/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;31;add_test;/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;0;")
add_test(test_directed_graph "/home/anxx/prog/project_of_algoritms/Graph_library/build/tests/test_directed_graph")
set_tests_properties(test_directed_graph PROPERTIES  _BACKTRACE_TRIPLES "/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;32;add_test;/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;0;")
add_test(test_undirected_graph "/home/anxx/prog/project_of_algoritms/Graph_library/build/tests/test_undirected_graph")
set_tests_properties(test_undirected_graph PROPERTIES  _BACKTRACE_TRIPLES "/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;33;add_test;/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;0;")
add_test(test_weighted_graph "/home/anxx/prog/project_of_algoritms/Graph_library/build/tests/test_weighted_graph")
set_tests_properties(test_weighted_graph PROPERTIES  _BACKTRACE_TRIPLES "/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;34;add_test;/home/anxx/prog/project_of_algoritms/Graph_library/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
