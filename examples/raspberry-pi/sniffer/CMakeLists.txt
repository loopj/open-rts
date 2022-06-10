add_executable(openrts-sniffer sniffer.c)

target_compile_definitions(openrts PUBLIC
    OPENRTS_HAS_GPIOD
)

target_compile_definitions(openrts-sniffer PRIVATE
	OPENRTS_BOARD_RASPBERRY_PI_RFM69_BONNET
)

target_link_libraries(openrts gpiod)
target_link_libraries(openrts-sniffer openrts)