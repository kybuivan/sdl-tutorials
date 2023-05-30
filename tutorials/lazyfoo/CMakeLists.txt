set(projects
    hello_world
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
