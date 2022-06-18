#ifndef RTS_RADIO_RFM69_HPP
#define RTS_RADIO_RFM69_HPP

#include "RTSRadio.hpp"

class RTSRadio_RFM69 : public RTSRadio
{
  public:
    RTSRadio_RFM69(SPIModule *spiModule) :
        RTSRadio(spiModule)
    {
    }

    RTSRadio_RFM69(uint8_t chipSelect) :
        RTSRadio(chipSelect)
    {
    }

    void begin()
    {
        RTSRadio::begin();
        rts_radio_init_rfm69(this, spiModule);
    }
};

#endif // RTS_RADIO_RFM69_HPP