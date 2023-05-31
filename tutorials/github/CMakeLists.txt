set(projects
    wenova
    snake
    hi-lo
    maze
    chess
    pong
    sokoban
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
