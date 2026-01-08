cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0144 NEW)
project(test VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(NOT TARGET Matrix)
    add_library(Matrix STATIC 
        src/Matrix.cpp
    )
    target_include_directories(Matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()


if(NOT TARGET testi)
    add_executable(testi
        test/main.cpp
    )
    target_link_libraries(testi PRIVATE Matrix)
    target_include_directories(testi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

endif()
set(GTEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/googletest/build")
set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/../googletest/include")
set(GTEST_LIBRARY "${GTEST_ROOT}/lib/Debug/gtestd.lib")
set(GTEST_MAIN_LIBRARY "${GTEST_ROOT}/lib/Debug/gtest_maind.lib")
enable_testing()
add_subdirectory(${GTEST_ROOT}/..)

add_executable(tests tests/Matrix_test.cpp)
target_link_libraries(tests PRIVATE Matrix gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)