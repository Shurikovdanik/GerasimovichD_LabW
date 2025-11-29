cmake_minimum_required(VERSION 3.16)
project(PhilosophersProblem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PhilosophersProblem
    PhilSemaphoreSolution.cpp
    StdAfx.cpp
    StdAfx.h
    Resource.h
)

# Windows GUI subsystem
if (WIN32)
    target_link_libraries(PhilosophersProblem PRIVATE user32 gdi32 comdlg32 advapi32)
    target_compile_definitions(PhilosophersProblem PRIVATE UNICODE _UNICODE)
    set_target_properties(PhilosophersProblem PROPERTIES
        WIN32_EXECUTABLE ON
    )
endif()
