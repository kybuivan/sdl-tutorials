set(projects
    wenova
    snake
    hi-lo
    maze
    chess
    pong
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
