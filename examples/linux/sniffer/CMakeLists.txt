cmake_minimum_required(VERSION 3.13)

project(sniffer
    VERSION 1.0
    DESCRIPTION "Open RTS Sniffer Example"
    LANGUAGES C
)

set(OPENRTS_HAS_GPIOD 1)

add_subdirectory(../../.. openrts)

add_executable(sniffer
    sniffer.c
)

target_link_libraries(sniffer
    openrts
    gpiod
)