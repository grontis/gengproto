find_package(SDL2 REQUIRED)

add_library(sdl_library SDLManager.cpp)

target_include_directories(sdl_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})

target_link_libraries(sdl_library ${SDL2_LIBRARIES})