#ifndef RTS_RADIO_RFM69_HPP
#define RTS_RADIO_RFM69_HPP

#include "RTSRadio.hpp"

class RTSRadio_RFM69 : public RTSRadio
{
  public:
    #if defined(ARDUINO)
    RTSRadio_RFM69(uint8_t chipSelect, bool paBoost = true, SPIClass *spiDevice=&SPI) :
        RTSRadio(chipSelect, spiDevice),
        paBoost(paBoost)
    {

    }

    void begin()
    {
        RTSRadio::begin();
        rts_radio_init_rfm69(this, &spi, paBoost);
    }
    #else
    RTSRadio_RFM69(spi_module *spi, bool paBoost = true)
    {
        rts_radio_init_rfm69(this, spi, paBoost);
    }
    #endif

  private:
    #if defined(ARDUINO)
    bool paBoost;
    #endif
};

#endif // RTS_RADIO_RFM69_HPP