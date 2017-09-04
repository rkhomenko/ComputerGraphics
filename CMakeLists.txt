cmake_minimum_required(VERSION 2.8.11)

project(ComputerGraphicsLabs)

set(CANVAS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/canvas/include")
set(CANVAS_LIBRARY_NAME "canvas")

add_subdirectory(canvas)
add_subdirectory(lab01)
