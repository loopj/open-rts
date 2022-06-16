#ifndef RTS_RADIO_SX1278_HPP
#define RTS_RADIO_SX1278_HPP

#include "RTSRadio.hpp"

class RTSRadio_SX1278 : public RTSRadio
{
  public:
    #if defined(ARDUINO)
    RTSRadio_SX1278(uint8_t chipSelect, bool paBoost = true, SPIClass *spiDevice=&SPI) :
        RTSRadio(chipSelect, spiDevice),
        paBoost(paBoost)
    {

    }

    void begin()
    {
        RTSRadio::begin();
        rts_radio_init_sx1278(this, &spi, paBoost);
    }
    #else
    RTSRadio_SX1278(spi_module *spi, bool paBoost = true)
    {
        rts_radio_init_sx1278(this, spi, paBoost);
    }
    #endif

  private:
    #if defined(ARDUINO)
    bool paBoost;
    #endif
};

#endif // RTS_RADIO_SX1278_HPP