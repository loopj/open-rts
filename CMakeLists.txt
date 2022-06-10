cmake_minimum_required(VERSION 3.13)

project(openrts
    VERSION 1.0
    DESCRIPTION "Open RTS"
    LANGUAGES C
)

add_library(openrts STATIC)

target_sources(openrts PRIVATE
    src/hal.c
    src/rts_command.c
    src/rts_frame_builder.c
    src/rts_frame.c
    src/rts_pulse_output.c
    src/rts_pulse_source.c
    src/rts_radio.c
    src/rts_receiver.c
    src/rts_remote_store_memory.c
    src/rts_remote_store.c
    src/rts_remote.c
    src/rts_timings.c

    src/ookradio/hal/spi_module.c
    src/ookradio/drivers/rfm69/rfm69.c
    src/ookradio/drivers/sx1278/sx1278.c
)

include(CheckSymbolExists)

if(ESP_PLATFORM)
    target_sources(openrts PRIVATE
        src/espidf/rts_pulse_output_espidf_gpio.c
        src/espidf/rts_pulse_source_espidf_gpio.c
        src/ookradio/hal/targets/espidf/spi_module_espidf.c
        # src/espidf/rts_remote_store_nvs.c
    )
endif()

# Build the mmap remote store when mmap is available
check_symbol_exists(mmap "sys/mman.h" OPENRTS_HAVE_MMAP)
if(OPENRTS_HAVE_MMAP)
    target_sources(openrts PRIVATE
        src/linux/rts_remote_store_mmap.c
    )
endif()

if(OPENRTS_HAS_GPIOD)
    target_sources(openrts PRIVATE
        src/linux/rts_pulse_source_gpiod.c
        src/linux/rts_pulse_output_gpiod.c
    )

    target_compile_definitions(openrts PRIVATE
        OPENRTS_HAS_GPIOD
    )
endif()

if(UNIX)
    target_sources(openrts PRIVATE
        src/ookradio/hal/targets/linux/spi_module_linux.c
    )
endif()

target_include_directories(openrts PUBLIC src)