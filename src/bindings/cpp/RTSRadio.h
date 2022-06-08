/**
 * @file
 * @addtogroup cpp
 *
 *  @{
 */

#ifndef RTS_RADIO_CPP_H
#define RTS_RADIO_CPP_H

#include "rts_radio.h"

/**
 * Abstraction layer which configures radio modules for RTS.
 */
class RTSRadio : protected rts_radio
{
  public:
	/**
	 * Set the radio mode for this module, eg. standby, receive, or transmit.
	 *
	 * @param mode the rts_radio_mode to enter
	 */
    void setMode(enum rts_radio_mode mode);

  protected:
    struct spi_module *defaultSPIModule(uint8_t chipSelect);
};

#endif // RTS_RADIO_CPP_H

/// @}