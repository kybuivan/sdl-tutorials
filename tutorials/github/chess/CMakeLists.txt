cmake_minimum_required(VERSION 3.21)

project(
    chess
    LANGUAGES C CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(chess ${SRC_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(
    chess
    PRIVATE ${LIBRARY_NAME})
