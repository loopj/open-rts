#ifndef RTS_RADIO_SX1278_HPP
#define RTS_RADIO_SX1278_HPP

#include "RTSRadio.hpp"

class RTSRadio_SX1278 : public RTSRadio
{
  public:
    RTSRadio_SX1278(SPIModule *spiModule) :
        RTSRadio(spiModule)
    {
    }

    RTSRadio_SX1278(uint8_t chipSelect, SPIModule *spiModule=&DEFAULT_SPI_MODULE) :
        RTSRadio(chipSelect, spiModule)
    {
    }

    void begin()
    {
        RTSRadio::begin();
        rts_radio_init_sx1278(this, spiModule);
    }
};

#endif // RTS_RADIO_SX1278_HPP