cmake_minimum_required(VERSION 3.13)

project(openrts-receiver
    VERSION 1.0
    DESCRIPTION "Open RTS Receiver Example"
    LANGUAGES C
)

set(OPENRTS_HAS_GPIOD 1)

add_executable(openrts-receiver receiver.c)
add_subdirectory(../../.. openrts)

target_compile_definitions(openrts-receiver PRIVATE
    OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
)

target_link_libraries(openrts-receiver openrts gpiod)