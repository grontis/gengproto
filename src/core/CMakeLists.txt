find_package(SDL2 REQUIRED)

add_subdirectory(colors)
add_subdirectory(shapes)

add_library(core_library STATIC RandomGenerator.cpp GraphicsManager.cpp EventManager.cpp)

target_include_directories(core_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})

target_link_libraries(core_library PUBLIC shapes_library ${SDL2_LIBRARIES})