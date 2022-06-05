#pragma once

#include "radio/spi_module_arduino.h"

#include "RTSRadio.h"

class RTSRadio_SX1278 : public RTSRadio {
  public:
    RTSRadio_SX1278(spi_module *spi, bool use_pa_boost) {
		rts_radio_init_sx1278(this, spi, use_pa_boost);
	}
};