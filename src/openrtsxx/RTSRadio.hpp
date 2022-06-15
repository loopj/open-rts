#ifndef RTS_RADIO_HPP
#define RTS_RADIO_HPP

#include <openrts/rts_radio.h>

#if defined(ARDUINO)
#include <SPI.h>
#endif

/**
 * @file
 */

/**
 * @addtogroup openrtsxx
 * @{
 */

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
    #if defined(ARDUINO)
    struct spi_module *initArduinoSPI(uint8_t chipSelect, SPIClass *spiDevice);
    struct spi_module spi = {};
    #endif
};

/**
 * @}
 */

#endif // RTS_RADIO_HPP