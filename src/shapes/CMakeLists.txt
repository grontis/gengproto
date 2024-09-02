add_library(shapes_library GRectangle.cpp)

target_include_directories(shapes_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})