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


if(build_windows STREQUAL "true" AND NOT WIN32)
     set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
     include_directories(./include)
     link_directories(./lib)
     add_compile_options(-L./lib -I./include)
else()
     set(CMAKE_CXX_COMPILER g++)
endif()

add_compile_options(-Wall -Wextra)
add_executable(ph ./src/main.cpp ${sources})

if(all_libs STREQUAL "true")
    target_link_libraries(ph PRIVATE m raylib opengl32 gdi32 winmm gcc stdc++ winpthread)
else()
    target_link_libraries(ph PRIVATE m raylib)
endif()
