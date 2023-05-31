cmake_minimum_required(VERSION 3.21)

project(
    mine-sweeper
    LANGUAGES C CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(mine-sweeper ${SRC_FILES})

target_link_libraries(
    mine-sweeper
    PRIVATE ${LIBRARY_NAME})
