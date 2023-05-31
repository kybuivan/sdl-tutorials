set(projects
    wenova
    snake
    hi-lo
    maze
    chess
    pong
    sokoban
    mine-sweeper
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
