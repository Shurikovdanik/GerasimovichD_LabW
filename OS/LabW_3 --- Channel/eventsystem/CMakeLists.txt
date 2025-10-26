cmake_minimum_required(VERSION 3.18)
project(EventSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

if(NOT TARGET Events)
    add_library(Events STATIC
        src/Event.cpp
        src/EventListener.cpp
        src/BasicObject.cpp
    )
    target_include_directories(Events PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()