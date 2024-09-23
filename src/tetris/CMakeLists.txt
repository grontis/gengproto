add_library(tetris_library Tetris.cpp Piece.cpp Grid.cpp PieceTemplates.cpp)

target_link_libraries(tetris_library core_library ${SDL2_LIBRARIES})

target_include_directories(tetris_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} core)