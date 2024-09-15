cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PacketHunter VERSION 1.0)

set(sources
    ./src/PacketHunter.cpp
    ./src/Gui/PacketHunterGui.cpp
    ./src/Gui/Windows.cpp
    ./src/Gui/WindowManager.cpp
    ./src/Devices/Devices.cpp
)

if(static STREQUAL "true")
    add_compile_options(-static)
endif()

if(debug STREQUAL "true")
    add_compile_options(-g)
else()
    add_compile_options(-O2)
endif()

add_compile_options(-Wall -Wextra)
add_executable(ph ./src/main.cpp ${sources})

target_link_libraries(ph PRIVATE m raylib)
