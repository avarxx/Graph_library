cmake_minimum_required(VERSION 3.10)
project(MyGraphProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -fsanitize=address")

add_custom_target(coverage
        COMMAND ctest --output-on-failure
        COMMAND lcov --capture --directory . --output-file coverage.info
        COMMAND lcov --remove coverage.info '/usr/*' '*/tests/*' '*/external/*' -o coverage-filtered.info
        COMMAND genhtml coverage-filtered.info --output-directory coverage-report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report for all tests"
)

add_custom_target(valgrind
        COMMAND ${VALGRIND} --leak-check=full --error-exitcode=1 ./my_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running tests with Valgrind"
)

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