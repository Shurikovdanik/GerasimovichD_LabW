cmake_minimum_required(VERSION 3.10)

project(QueueApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем исходники
add_executable(QueueApp
    Queue.cpp
    Resource.h
)

# Для Windows GUI приложения
if (WIN32)
    target_link_libraries(QueueApp PRIVATE
        user32
        gdi32
        comdlg32
        advapi32
    )
endif()
