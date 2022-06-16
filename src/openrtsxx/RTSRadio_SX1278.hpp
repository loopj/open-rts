#ifndef RTS_RADIO_SX1278_HPP
#define RTS_RADIO_SX1278_HPP

#include "RTSRadio.hpp"

class RTSRadio_SX1278 : public RTSRadio
{
  public:
    #if defined(ARDUINO)
    RTSRadio_SX1278(uint8_t chipSelect, bool paBoost = true, SPIClass *spiDevice=&SPI)
    {
        rts_radio_init_sx1278(this, initArduinoSPI(chipSelect, spiDevice), paBoost);
    }
    #endif

    RTSRadio_SX1278(spi_module *spi, bool paBoost = true)
    {
        rts_radio_init_sx1278(this, spi, paBoost);
    }
};

#endif // RTS_RADIO_SX1278_HPP