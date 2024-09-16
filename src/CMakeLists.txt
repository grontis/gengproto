add_subdirectory(core)
add_subdirectory(shapes)

set(SOURCES
    Entity.cpp
    Game.cpp
    main.cpp
)

add_executable(gengproto ${SOURCES})

target_link_libraries(gengproto core_library shapes_library ${SDL2_LIBRARIES})

target_include_directories(gengproto PUBLIC core shapes)