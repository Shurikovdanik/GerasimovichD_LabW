cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0144 NEW)
project(test VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Don't hardcode Debug mode - use build types or default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Remove Windows-specific flags
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)  # Windows only

# Enable position independent code for shared libraries (important for Ubuntu)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Library: Num (static)
if(NOT TARGET Num)
    add_library(Num STATIC 
        src/Number.cpp
    )
    target_include_directories(Num PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

# Library: Vector (shared)
if(NOT TARGET Vector)
    add_library(Vector SHARED 
        src/Vector.cpp
    )
    target_include_directories(Vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    # Link against Num target, not file path
    target_link_libraries(Vector PRIVATE Num)
endif()

# Executable: testi
if(NOT TARGET testi)
    add_executable(testi
        test/main.cpp
    )
    target_include_directories(testi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    # Link against targets, not file paths
    target_link_libraries(testi PRIVATE Num Vector)
endif()

# Google Test Configuration for Ubuntu/GCC
# Option 1: Using FetchContent (Recommended - automatic download)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0  
)

FetchContent_MakeAvailable(googletest)


enable_testing()

# Test executable
add_executable(tests 
    tests/test_number.cpp 
    tests/test_vectors.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE Num GTest::gtest GTest::gtest_main)

# Discover and add tests
include(GoogleTest)
gtest_discover_tests(tests)