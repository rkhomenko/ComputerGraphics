cmake_minimum_required(VERSION 2.8.11)

project(ComputerGraphicsLabs)

set(OPENGLWINDOW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/OpenGLWindow/include")
set(OPENGLWINDOW_LIBRARY_NAME "OpenGLWindow")

add_subdirectory(OpenGLWindow)
add_subdirectory(lab01)
