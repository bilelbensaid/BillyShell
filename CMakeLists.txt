cmake_minimum_required(VERSION 3.28)
project(untitled18 C)

set(CMAKE_C_STANDARD 11)
find_library(READLINE_LIB readline)

include_directories(include)

add_executable(untitled18

        src/main.c
        src/minishell.c
        src/libft.c
)

if(READLINE_LIB)
    target_link_libraries(untitled18 ${READLINE_LIB})
else()
    message(FATAL_ERROR "La librairie readline est introuvable !")
endif()