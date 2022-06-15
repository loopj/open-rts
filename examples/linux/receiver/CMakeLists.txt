cmake_minimum_required(VERSION 3.13)

project(receiver
    VERSION 1.0
    DESCRIPTION "Open RTS Receiver Example"
    LANGUAGES C
)

set(OPENRTS_HAS_GPIOD 1)

add_executable(receiver receiver.c)
add_subdirectory(../../.. openrts)

target_compile_definitions(receiver PRIVATE
    OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
)

target_link_libraries(receiver openrts gpiod)