add_executable(openrts-receiver receiver.c)

target_compile_definitions(openrts PUBLIC
    OPENRTS_HAS_GPIOD
)

target_compile_definitions(openrts-receiver PRIVATE
    OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
)

target_link_libraries(openrts gpiod)
target_link_libraries(openrts-receiver openrts)