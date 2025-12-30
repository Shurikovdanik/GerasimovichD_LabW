cmake_minimum_required(VERSION 3.16)
project(PipesApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/main.cpp)
add_executable(procM src/ProcM.cpp)
add_executable(procA src/ProcA.cpp)
add_executable(procP src/ProcP.cpp)
add_executable(procS src/ProcS.cpp)
