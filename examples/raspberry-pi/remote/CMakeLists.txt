cmake_minimum_required(VERSION 3.13)

project(openrts-remote
    VERSION 1.0
    DESCRIPTION "Open RTS Remote Example"
    LANGUAGES C
)

add_executable(openrts-remote remote.c)
add_subdirectory(../../.. openrts)

target_compile_definitions(openrts PUBLIC
    OPENRTS_HAS_GPIOD
)

target_compile_definitions(openrts-remote PRIVATE
    OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
)

target_link_libraries(openrts-remote openrts gpiod)