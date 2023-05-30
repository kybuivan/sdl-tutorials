set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cc")

set(PROJECT_NAME hello_world)

add_executable(${PROJECT_NAME} ${APP_SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${LIBRARY_NAME})
