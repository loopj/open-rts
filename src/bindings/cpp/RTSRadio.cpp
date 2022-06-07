#include "config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSRadio.h"

#if defined(ARDUINO)
#include "radio/spi_module_arduino.h"
#endif

void RTSRadio::setMode(rts_radio_mode mode)
{
    rts_radio_set_mode(this, mode);
}

struct spi_module *RTSRadio::defaultSPIModule(uint8_t chipSelect)
{
	#if defined(ARDUINO)
	static struct spi_module spi = {
		.cs_pin = chipSelect,
		.clock = 1000000,
		.mode = 0,
	};
	spi_module_init_arduino(&spi);

	return &spi;
	#else
	return nullptr;
	#endif
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS