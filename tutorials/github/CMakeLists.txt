set(projects
    wenova
    snake
    hi-lo
    maze
    chess
    pong
    sokoban
    mine-sweeper
    game-of-life
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
