add_library(openrts STATIC)

target_sources(openrts PRIVATE
    hal.c
    rts_command.c
    rts_frame_builder.c
    rts_frame.c
    rts_pulse_output.c
    rts_pulse_source.c
    rts_radio.c
    rts_receiver.c
    rts_remote_store_memory.c
    rts_remote_store.c
    rts_remote.c
    rts_timings.c
)

target_include_directories(openrts
    INTERFACE ..
    PRIVATE .
)

target_link_libraries(openrts
    PRIVATE ookradio
)

# Include ESP-IDF pulse_output, pulse_source, and remote_store when available
if(ESP_PLATFORM)
    target_sources(openrts PRIVATE
        espidf/rts_pulse_output_espidf_gpio.c
        espidf/rts_pulse_source_espidf_gpio.c
        espidf/rts_remote_store_nvs.c
    )

    target_link_libraries(openrts PRIVATE idf::nvs_flash)
endif()

# Include memory-mapped remote_store when available
include(CheckSymbolExists)
check_symbol_exists(mmap "sys/mman.h" OPENRTS_HAVE_MMAP)
if(OPENRTS_HAVE_MMAP)
    target_sources(openrts PRIVATE
        linux/rts_remote_store_mmap.c
    )
endif()

# Include gpiod pulse_source/pulse_output when enabled
if(OPENRTS_HAS_GPIOD)
    target_sources(openrts PRIVATE
        linux/rts_pulse_source_gpiod.c
        linux/rts_pulse_output_gpiod.c
    )

    target_compile_definitions(openrts PUBLIC
        OPENRTS_HAS_GPIOD
    )
endif()