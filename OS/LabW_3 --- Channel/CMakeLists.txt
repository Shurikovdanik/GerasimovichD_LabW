cmake_minimum_required(VERSION 3.18)
project(test VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
if (MSVC)
    add_compile_options(/utf-8)
endif()

add_library(Num STATIC IMPORTED)

set_target_properties(Num PROPERTIES
    IMPORTED_LOCATION   "${CMAKE_CURRENT_SOURCE_DIR}/lib/Num.lib"   
)
include(FetchContent)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.12.0 
)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)



FetchContent_MakeAvailable(spdlog googletest)
if(NOT TARGET Tunnel)
    add_library(Tunnel SHARED 
        src/ThreadTunnel.cpp
    )
    link_libraries(Num spdlog::spdlog)
    target_include_directories(Tunnel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/spdlog-src/include)
endif()
if(NOT TARGET Matrix)
    add_library(Matrix STATIC 
        src/Matrix.cpp
    )
    link_libraries(Num spdlog::spdlog)
    target_include_directories(Matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/spdlog-src/include)
endif()


if(NOT TARGET testi)
    add_executable(testi
        test/main.cpp
    )
    target_link_libraries(testi PRIVATE Num Matrix)
    target_include_directories(testi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

endif()
if(NOT TARGET tests)
    add_executable(tests
        tests/Matrix_test.cpp
        tests/Tunnel_test.cpp
    )
    include(GoogleTest)
    target_link_libraries(tests PRIVATE Num Matrix Tunnel gtest_main)
    target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/googletest-src ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/spdlog-src)

endif()
enable_testing()
gtest_discover_tests(tests)