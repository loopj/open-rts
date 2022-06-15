cmake_minimum_required(VERSION 3.13)

project(receiver
    VERSION 1.0
    DESCRIPTION "Open RTS Receiver Example"
    LANGUAGES C
)

set(OPENRTS_HAS_GPIOD 1)

add_subdirectory(../../.. openrts)

add_executable(receiver
    receiver.c
)

target_link_libraries(receiver
    openrts
    gpiod
)