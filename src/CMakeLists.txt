add_subdirectory(core)

set(SOURCES
    Entity.cpp
    Game.cpp
    main.cpp
)

add_executable(gengproto ${SOURCES})

target_link_libraries(gengproto core_library ${SDL2_LIBRARIES})

target_include_directories(gengproto PUBLIC core shapes)