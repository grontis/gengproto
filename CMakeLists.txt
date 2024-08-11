cmake_minimum_required(VERSION 3.10)
project(gengproto)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(gengproto main.cpp)
target_link_libraries(gengproto ${SDL2_LIBRARIES})