#pragma once

#include "radio/spi_module_arduino.h"

#include "RTSRadio.h"

class RTSRadio_RFM69 : public RTSRadio {
  public:
    RTSRadio_RFM69(spi_module *spi, bool use_pa_boost) {
		rts_radio_init_rfm69(this, spi, use_pa_boost);
	}
};