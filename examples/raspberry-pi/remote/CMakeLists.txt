cmake_minimum_required(VERSION 3.13)

project(remote
    VERSION 1.0
    DESCRIPTION "Open RTS Remote Example"
    LANGUAGES C
)

set(OPENRTS_HAS_GPIOD 1)

add_executable(remote remote.c)
add_subdirectory(../../.. openrts)

target_compile_definitions(remote PRIVATE
    OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
)

target_link_libraries(remote openrts gpiod)