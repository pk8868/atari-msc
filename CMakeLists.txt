cmake_minimum_required(VERSION 3.24)

project(atari-msc VERSION 1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(COPY "atari/assets" DESTINATION ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("atari")
