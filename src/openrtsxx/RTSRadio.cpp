#include "RTSRadio.hpp"

#if defined(ARDUINO)
#include "ookradio/hal/targets/arduino/spi_module_arduino.h"
#endif

void RTSRadio::setMode(enum rts_radio_mode mode)
{
    rts_radio_set_mode(this, mode);
}

struct spi_module *RTSRadio::defaultSPIModule(uint8_t chipSelect)
{
#if defined(ARDUINO)
    static struct spi_module spi;
    spi.cs_pin = chipSelect;
    spi.clock  = 1000000;
    spi.mode   = 0;

    spi_module_init_arduino(&spi);

    return &spi;
#else
    return nullptr;
#endif
}