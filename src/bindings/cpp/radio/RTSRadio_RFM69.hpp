#ifndef RTS_RADIO_RFM69_HPP
#define RTS_RADIO_RFM69_HPP

#include "bindings/cpp/RTSRadio.hpp"

class RTSRadio_RFM69 : public RTSRadio
{
  public:
    RTSRadio_RFM69(uint8_t chipSelect, bool paBoost = true)
    {
        rts_radio_init_rfm69(this, defaultSPIModule(chipSelect), paBoost);
    }

    RTSRadio_RFM69(uint8_t chipSelect, bool paBoost, spi_module *spi)
    {
        rts_radio_init_rfm69(this, spi, paBoost);
    }
};

#endif // RTS_RADIO_RFM69_HPP