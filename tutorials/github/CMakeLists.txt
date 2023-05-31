set(projects
    wenova
)

foreach(projname ${projects})
    add_subdirectory(${projname})
endforeach()
