cmake_minimum_required(VERSION 3.13)

project(remote
    VERSION 1.0
    DESCRIPTION "Open RTS Remote Example"
    LANGUAGES C
)

set(OPENRTS_HAS_GPIOD 1)

add_subdirectory(../../.. openrts)

add_executable(remote
    remote.c
)

target_link_libraries(remote
    openrts
    gpiod
)