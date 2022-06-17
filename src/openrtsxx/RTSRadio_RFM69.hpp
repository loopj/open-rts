#ifndef RTS_RADIO_RFM69_HPP
#define RTS_RADIO_RFM69_HPP

#if defined(ARDUINO)

#include "RTSRadio.hpp"

class RTSRadio_RFM69 : public RTSRadio
{
  public:
    RTSRadio_RFM69(uint8_t chipSelect, SPIClass *spiDevice=&SPI) :
        RTSRadio(chipSelect, spiDevice)
    {

    }

    void begin()
    {
        RTSRadio::begin();
        rts_radio_init_rfm69(this, &spi);
    }
};

#endif // defined(ARDUINO)

#endif // RTS_RADIO_RFM69_HPP