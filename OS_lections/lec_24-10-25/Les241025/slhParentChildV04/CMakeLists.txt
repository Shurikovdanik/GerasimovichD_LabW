cmake_minimum_required(VERSION 3.18)
project(EventSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
if (MSVC)
    add_compile_options(/utf-8)
endif()


if (NOT TARGET Child)
add_executable(Child
Parent/Parent.cpp
)
target_include_directories(Child PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Parent)
endif()

if (NOT TARGET Parent)
add_executable(Parent 
Parent/Parent.cpp
)
target_include_directories(Parent PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Parent)
endif()
