#ifndef RTS_RADIO_HPP
#define RTS_RADIO_HPP

#include <openrts/rts_radio.h>

/**
 * @file
 */

/**
 * @addtogroup openrtsxx
 * @{
 */

class SPIModule : public spi_module
{
  public:
    SPIModule()
    {
        clock = 1000000;
        mode = 0;
    }

    virtual void begin() = 0;
};

#if defined(ARDUINO)
class ArduinoSPI : public SPIModule
{
  public:
    ArduinoSPI(SPIClass *spiClass=&SPI) :
        spiClass(spiClass)
    {
    }

    void begin()
    {
        spi_module_init_arduino(this, spiClass);
    }

  private:
    SPIClass *spiClass;
};

ArduinoSPI DEFAULT_SPI_MODULE;
#endif

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
    void setMode(enum rts_radio_mode mode)
    {
        rts_radio_set_mode(this, mode);
    }

  protected:
    RTSRadio(SPIModule *spiModule) :
        spiModule(spiModule)
    {
    }

    RTSRadio(uint8_t chipSelect, SPIModule *spiModule) :
        spiModule(spiModule)
    {
        this->spiModule->cs_pin = chipSelect;
    }

    void begin()
    {
        spiModule->begin();
    }

    SPIModule *spiModule;
};

/**
 * @}
 */

#endif // RTS_RADIO_HPP