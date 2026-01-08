cmake_minimum_required(VERSION 3.16)
project(PipesApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(BIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_OUTPUT_DIR})

add_executable(main src/main.cpp)
add_executable(procM src/ProcM.cpp)
add_executable(procA src/ProcA.cpp)
add_executable(procP src/ProcP.cpp)
add_executable(procS src/ProcS.cpp)
