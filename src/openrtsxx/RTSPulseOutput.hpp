#ifndef RTS_PULSE_OUTPUT_HPP
#define RTS_PULSE_OUTPUT_HPP

#include <openrts/rts_pulse_output.h>

/**
 * @file
 */

/**
 * @addtogroup openrtsxx
 * @{
 */

/**
 * Provides an interface for an output of RTS pulses, eg a GPIO or radio.
 *
 * Implementations must define the `enable`, `disable`, and `send_pulse`
 * functions and set the function pointers in the rts_pulse_output struct.
 */
class RTSPulseOutput : protected rts_pulse_output
{
  public:
    ~RTSPulseOutput();

    /**
     * Enable the pulse output.
     */
    void enable();

    /**
     * Disable the pulse output.
     */
    void disable();

    /**
     * Instruct the rts_pulse_output to output a pulse.
     *
     * @param state boolean pulse logic state, true = HIGH, false = LOW
     * @param micros the time the pulse was in this state, in microseconds
     */
    void sendPulse(bool state, uint32_t micros);

  protected:
    RTSPulseOutput();

    friend class RTSRemote;
};

/**
 * @}
 */

#endif // RTS_PULSE_OUTPUT_HPP