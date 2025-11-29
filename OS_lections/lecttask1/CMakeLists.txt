cmake_minimum_required(VERSION 3.10)

project(PipelineTask LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pipeline
    main.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pipeline PRIVATE -Wall -Wextra -pedantic)
endif()

if (MSVC)
    target_compile_options(pipeline PRIVATE /W4)
endif()
