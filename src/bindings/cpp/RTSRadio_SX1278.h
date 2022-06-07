#ifndef RTS_RADIO_SX1278_CPP_H
#define RTS_RADIO_SX1278_CPP_H

#include "RTSRadio.h"

class RTSRadio_SX1278 : public RTSRadio
{
  public:
    RTSRadio_SX1278(spi_module *spi, bool use_pa_boost)
    {
        rts_radio_init_sx1278(this, spi, use_pa_boost);
    }
};

#endif // RTS_RADIO_SX1278_CPP_H