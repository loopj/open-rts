cmake_minimum_required(VERSION 3.13)

project(openrts-sniffer
    VERSION 1.0
    DESCRIPTION "Open RTS Sniffer Example"
    LANGUAGES C
)

add_executable(openrts-sniffer sniffer.c)
add_subdirectory(../../.. openrts)

target_compile_definitions(openrts PUBLIC
    OPENRTS_HAS_GPIOD
)

target_compile_definitions(openrts-sniffer PRIVATE
    OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
)

target_link_libraries(openrts-sniffer openrts gpiod)