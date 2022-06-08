#ifndef RTS_RADIO_SX1278_CPP_H
#define RTS_RADIO_SX1278_CPP_H

#include "bindings/cpp/RTSRadio.h"

class RTSRadio_SX1278 : public RTSRadio
{
  public:
    RTSRadio_SX1278(uint8_t chipSelect, bool paBoost = true)
    {
        rts_radio_init_sx1278(this, defaultSPIModule(chipSelect), paBoost);
    }

    RTSRadio_SX1278(uint8_t chipSelect, bool paBoost, spi_module *spi)
    {
        rts_radio_init_sx1278(this, spi, paBoost);
    }
};

#endif // RTS_RADIO_SX1278_CPP_H