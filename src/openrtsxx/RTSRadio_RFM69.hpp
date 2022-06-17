#ifndef RTS_RADIO_RFM69_HPP
#define RTS_RADIO_RFM69_HPP

#include "RTSRadio.hpp"

class RTSRadio_RFM69 : public RTSRadio
{
  public:
    #if defined(ARDUINO)
    RTSRadio_RFM69(uint8_t chipSelect, SPIClass *spiDevice=&SPI) :
        RTSRadio(chipSelect, spiDevice)
    {

    }

    void begin()
    {
        RTSRadio::begin();
        rts_radio_init_rfm69(this, &spi);
    }
    #else
    RTSRadio_RFM69(spi_module *spi)
    {
        rts_radio_init_rfm69(this, spi);
    }
    #endif
};

#endif // RTS_RADIO_RFM69_HPP