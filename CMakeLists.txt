cmake_minimum_required(VERSION 3.12)
project(example_cxx)

set(CMAKE_CXX_STANDARD 11)

add_executable(example_cxx main.cpp test_common/test_traverse.hpp test_common/test_lambda.hpp test_algorithm/test_sort.hpp)