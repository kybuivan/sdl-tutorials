# Sources and Headers
file(GLOB LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB LIBRARY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# MyLib Library
add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})
target_link_libraries(
    ${LIBRARY_NAME}
    PUBLIC nlohmann_json::nlohmann_json
            fmt::fmt
            spdlog::spdlog
            SDL2::SDL2-static
            SDL2::SDL2main
            SDL2_image
            SDL2_mixer
            SDL2_ttf
            SDL2_net
            cxxopts::cxxopts)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${LIBRARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${LIBRARY_NAME}
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${LIBRARY_NAME})
endif()
