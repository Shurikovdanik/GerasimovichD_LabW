cmake_minimum_required(VERSION 3.18)

project(test VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


if(NOT TARGET Num)
    add_library(Num STATIC 
        src/Number.cpp
    )
    target_include_directories(Num PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()
if(NOT TARGET Vector)
    add_library(Vector SHARED 
        src/Vector.cpp
    )
    target_include_directories(Vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(Vector PRIVATE Num)
endif()

if(NOT TARGET test)
    add_executable(test
        test/main.cpp
    )

    target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    target_link_libraries(test PRIVATE Num Vector)
endif()
