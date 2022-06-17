#ifndef RTS_RADIO_SX1278_HPP
#define RTS_RADIO_SX1278_HPP

#include "RTSRadio.hpp"

class RTSRadio_SX1278 : public RTSRadio
{
  public:
    #if defined(ARDUINO)
    RTSRadio_SX1278(uint8_t chipSelect, SPIClass *spiDevice=&SPI) :
        RTSRadio(chipSelect, spiDevice)
    {

    }

    void begin()
    {
        RTSRadio::begin();
        rts_radio_init_sx1278(this, &spi);
    }
    #else
    RTSRadio_SX1278(spi_module *spi)
    {
        rts_radio_init_sx1278(this, spi);
    }
    #endif
};

#endif // RTS_RADIO_SX1278_HPP