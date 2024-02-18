cmake_minimum_required(VERSION 3.27)
project(Stack)

set(CMAKE_CXX_STANDARD 20)

add_library(Stack INTERFACE include/stack.hpp)
target_include_directories(Stack INTERFACE include)

add_executable(sand sandbox.cpp)
target_link_libraries(sand PRIVATE Stack)