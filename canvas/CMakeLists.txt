cmake_minimum_required(VERSION 2.8.11)

project(canvas)

set(INCLUDE_DIR "include")
set(SOURCE_DIR "src")
set(INCLUDE_SUF "hpp")
set(SOURCE_SUF "cpp")

file(GLOB_RECURSE INCLUDES "${INCLUDE_DIR}/*.${INCLUDE_SUF}")
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.${SOURCE_SUF}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

include_directories(
    ${INCLUDE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} SHARED ${INCLUDES} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
