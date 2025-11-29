cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)


project(Lectioning VERSION 1.0.0 LANGUAGES CXX)

add_executable(Redirecting DoPipeLine/DoPipeLine.cpp)
