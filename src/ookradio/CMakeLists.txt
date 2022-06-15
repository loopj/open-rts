add_library(ookradio STATIC)

target_sources(ookradio PRIVATE
    hal/spi_module.c
    drivers/rfm69/rfm69.c
    drivers/sx1278/sx1278.c
)

target_include_directories(ookradio
    INTERFACE ..
    PUBLIC .
)

# Include SPI hooks for ESP-IDF when available
if(ESP_PLATFORM)
    target_sources(ookradio PRIVATE
        hal/targets/espidf/spi_module_espidf.c
    )
endif()

# Include SPI hooks for Linux when available
if(UNIX)
    target_sources(ookradio PRIVATE
        hal/targets/linux/spi_module_linux.c
    )
endif()