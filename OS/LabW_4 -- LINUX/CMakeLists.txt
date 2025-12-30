cmake_minimum_required(VERSION 3.10)
project(ProcessKillerDemo)

set(CMAKE_CXX_STANDARD 17)

add_executable(Killer src/Killer.cpp)
add_executable(User src/User.cpp)
