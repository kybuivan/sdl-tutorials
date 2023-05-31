set(projects
    wenova
    snake
    hi-lo
    maze
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
