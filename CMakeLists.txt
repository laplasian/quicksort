cmake_minimum_required(VERSION 3.10)
project(quicksort_project CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wcast-qual -Wshadow)

add_executable(quicksort main.cpp)
target_compile_definitions(quicksort PRIVATE USE_CONCEPTS)

# SFINAE
add_executable(quicksort_tests_sfinae tests.cpp)
target_link_libraries(quicksort_tests_sfinae GTest::gtest_main)

# Concepts
add_executable(quicksort_tests_concepts tests.cpp)
target_compile_definitions(quicksort_tests_concepts PRIVATE USE_CONCEPTS)
target_link_libraries(quicksort_tests_concepts GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(quicksort_tests_sfinae)
gtest_discover_tests(quicksort_tests_concepts)