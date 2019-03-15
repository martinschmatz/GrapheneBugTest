cmake_minimum_required(VERSION 3.13)
project(GrapheneBugTesting)

set(CMAKE_CXX_STANDARD 14)

link_libraries(pthread)

add_executable(GrapheneBugTesting GrapheneBugTesting.cpp)