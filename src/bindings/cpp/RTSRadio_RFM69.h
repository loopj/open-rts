#ifndef RTS_RADIO_RFM69_CPP_H
#define RTS_RADIO_RFM69_CPP_H

#include "radio/spi_module_arduino.h"

#include "RTSRadio.h"

class RTSRadio_RFM69 : public RTSRadio {
  public:
    RTSRadio_RFM69(spi_module *spi, bool use_pa_boost) {
		rts_radio_init_rfm69(this, spi, use_pa_boost);
	}
};

#endif // RTS_RADIO_RFM69_CPP_H