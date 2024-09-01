cmake_minimum_required(VERSION 3.10)

project(gengproto)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES
    src/Coordinate.h
    src/Entity.cpp
    src/SDLManager.cpp
    src/Game.cpp
    src/main.cpp
)

add_executable(gengproto ${SOURCES})

target_link_libraries(gengproto ${SDL2_LIBRARIES})