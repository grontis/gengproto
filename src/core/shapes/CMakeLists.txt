add_library(shapes_library GRectangle.cpp)

target_link_libraries(shapes_library PUBLIC colors_library)

target_include_directories(shapes_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})