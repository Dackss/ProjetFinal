cmake_minimum_required(VERSION 3.25)
project(ProjetFinal C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

# All source files are gathered into one variable
set(PROJET_FINAL_SRC
        main.c
        src/htmlexport.c
        src/person.c
        src/filemanager.c
        src/population.c
        src/menu.c
        src/advanced.c
)

# Using the variable containing source files
add_executable(ProjetFinal ${PROJET_FINAL_SRC})
target_link_libraries(ProjetFinal m)