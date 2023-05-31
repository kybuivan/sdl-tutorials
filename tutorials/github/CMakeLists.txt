set(projects
    wenova
    snake
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
