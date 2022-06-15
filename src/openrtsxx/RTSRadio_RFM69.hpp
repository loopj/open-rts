#ifndef RTS_RADIO_RFM69_HPP
#define RTS_RADIO_RFM69_HPP

#include "RTSRadio.hpp"

#if defined(ARDUINO)
#include <SPI.h>
#endif

class RTSRadio_RFM69 : public RTSRadio
{
  public:
    #if defined(ARDUINO)
    RTSRadio_RFM69(uint8_t chipSelect, bool paBoost = true, SPIClass *spiDevice=&SPI)
    {
        rts_radio_init_rfm69(this, initArduinoSPI(chipSelect, spiDevice), paBoost);
    }
    #endif

    RTSRadio_RFM69(spi_module *spi, bool paBoost = true)
    {
        rts_radio_init_rfm69(this, spi, paBoost);
    }
};

#endif // RTS_RADIO_RFM69_HPP