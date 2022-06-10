idf_component_register(SRCS "remote.c" INCLUDE_DIRS "")

target_compile_definitions(${COMPONENT_LIB} PRIVATE
	OPENRTS_BOARD_SPARKFUN_LORA_GATEWAY=1
	OPENRTS_BUTTON_2=23
    OPENRTS_BUTTON_3=19
    OPENRTS_BUTTON_4=18
)

add_subdirectory(../../../.. openrts)
target_link_libraries(${COMPONENT_LIB} PUBLIC openrts)