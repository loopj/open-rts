#include "RTSRadio.hpp"

#if defined(ARDUINO)
#include <ookradio/hal/targets/arduino/spi_module_arduino.hpp>
#endif

void RTSRadio::setMode(enum rts_radio_mode mode)
{
    rts_radio_set_mode(this, mode);
}

#if defined(ARDUINO)
struct spi_module *RTSRadio::initArduinoSPI(uint8_t chipSelect, SPIClass *spiDevice){
    spi.cs_pin = chipSelect;
    spi.clock  = 1000000;
    spi.mode   = 0;

    spi_module_init_arduino(&spi, spiDevice);

    return &spi;
}
#endif