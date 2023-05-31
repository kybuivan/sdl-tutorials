set(projects
    wenova
    snake
    hi-lo
    maze
    chess
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
