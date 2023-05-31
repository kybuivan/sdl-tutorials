set(projects
    wenova
    snake
    hi-lo
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
