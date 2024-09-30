add_subdirectory(core)
add_subdirectory(tetris)

set(SOURCES
    main.cpp
)

add_executable(gengproto ${SOURCES})

target_link_libraries(gengproto core_library tetris_library ${SDL2_LIBRARIES})

target_include_directories(gengproto PUBLIC core tetris)