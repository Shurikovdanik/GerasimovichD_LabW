cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0144 NEW)
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
    target_link_libraries(Vector PRIVATE "C:\\games\\GerasimovichD_LabW\\OS\\Labw_1\\build\\Num.lib")
endif()

if(NOT TARGET testi)
    add_executable(testi
        test/main.cpp
    )

    target_include_directories(testi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    target_link_libraries(testi PRIVATE "C:\\games\\GerasimovichD_LabW\\OS\\Labw_1\\build\\Num.lib" "C:\\games\\GerasimovichD_LabW\\OS\\Labw_1\\build\\Vector.lib") #Тут .lib для win32, т.к. CMake передаёт эти пути в командную строку и именно в .lib лежит таблица символов (по dll просто fatal error LNK1107 будет)
endif()
set(GTEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/googletest/build")
set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/../googletest/include")
set(GTEST_LIBRARY "${GTEST_ROOT}/lib/Debug/gtestd.lib")
set(GTEST_MAIN_LIBRARY "${GTEST_ROOT}/lib/Debug/gtest_maind.lib")
enable_testing()
add_subdirectory(${GTEST_ROOT}/..)

add_executable(tests tests/test_number.cpp tests/test_vectors.cpp)
target_link_libraries(tests PRIVATE Num gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)