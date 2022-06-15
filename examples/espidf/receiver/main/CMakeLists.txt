idf_component_register(SRCS "receiver.c" INCLUDE_DIRS "")

target_compile_definitions(${COMPONENT_LIB} PRIVATE
	OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY
)

add_subdirectory(../../../.. openrts)
target_link_libraries(${COMPONENT_LIB} PUBLIC openrts)