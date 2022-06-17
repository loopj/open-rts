#ifndef RTS_RADIO_SX1278_HPP
#define RTS_RADIO_SX1278_HPP

#if defined(ARDUINO)

#include "RTSRadio.hpp"

class RTSRadio_SX1278 : public RTSRadio
{
  public:
    RTSRadio_SX1278(uint8_t chipSelect, SPIClass *spiDevice=&SPI) :
        RTSRadio(chipSelect, spiDevice)
    {

    }

    void begin()
    {
        RTSRadio::begin();
        rts_radio_init_sx1278(this, &spi, &sx1278);
    }

  private:
    struct sx1278 sx1278;
};

#endif // defined(ARDUINO)

#endif // RTS_RADIO_SX1278_HPP