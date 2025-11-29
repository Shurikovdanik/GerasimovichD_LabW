cmake_minimum_required(VERSION 3.10)

project(HandshakeApp LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Handshake
    Handshake.cpp
    Handshake.rc
)

if(WIN32)
    target_link_libraries(Handshake
        PRIVATE
        user32
        gdi32
        comdlg32
        advapi32
    )
endif()

set_target_properties(Handshake PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
