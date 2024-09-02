add_library(core_library STATIC RandomGenerator.cpp)

target_include_directories(core_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})