cmake_minimum_required(VERSION 3.27)
project(emulatorCPU)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps/StackLib)

set(SOURCES src/cpu.cpp
        src/parser.cpp
        src/preprocessor.cpp
        main.cpp
)

file(GLOB OPERATIONS operations/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${OPERATIONS})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE Stack)