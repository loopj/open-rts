#ifndef RTS_REMOTE_HPP
#define RTS_REMOTE_HPP

#include "rts_remote.h"

#include "RTSFrame.hpp"
#include "RTSPulseOutput.hpp"
#include "RTSRemoteStore.hpp"

/**
 * @file
 */

/**
 * @addtogroup cpp
 * @{
 */

/**
 * Simulates a physical RTS remote control.
 *
 * It takes RTS commands (button presses), converts them into a series of
 * pulses, then outputs those pulses to a RTSPulseOutput (eg. a GPIO or radio).
 *
 * Remote rolling codes can be persisted by providing a rts_remote_store backend
 * (eg. ESP32's non-volatile storage, or Arduino's EEPROM).
 */
class RTSRemote : public rts_remote
{
  public:
    /**
     * Construct a RTSRemote instance.
     *
     * @param output where to send pulses to
     * @param store where to get/set remote rolling codes
     * @param timings the rts_timings struct to use for pulse encoding
     */
    RTSRemote(RTSPulseOutput *output, RTSRemoteStore *store = nullptr,
              rts_timings *timings = RTS_TIMINGS_DEFAULT);

    /**
     * Send a "button press" command.
     *
     * This is the simplest way to use an RTSRemote, which automatically creates
     * an RTSFrame struct under the hood, and handles the incrementing of rolling
     * codes in the internal RTSRemoteStore.
     *
     * The generated RTSFrame is passed to RTSRemote::sendFrame.
     *
     * @param address the remote address to send from
     * @param command the rts command to send (see rts_command enum)
     * @param repeated is this a "repeated" command, eg. from a button being held
     *                 down? If so we won't increment the remote's rolling code
     */
    void sendCommand(uint32_t address, rts_command command,
                     bool repeated = false);


    /**
     * Send an RTS frame.
     *
     * This function converts the provided RTSFrame into a series of pulses, which
     * are passed along to the internal RTSPulseOutput by RTSRemote::sendPulse.
     *
     * @param frame the rts_frame to send
     * @param repeated is this a "repeated" command, eg. from a button being held
     *                 down? If so we won't increment the remote's rolling code
     */
    void sendFrame(RTSFrame *frame, bool repeated = false);

    /**
     * Send a single pulse to the internal RTSPulseOutput.
     *
     * @param state boolean pulse logic state, true = HIGH, false = LOW
     * @param micros how long to set the pulse to this state, in microseconds
     */
    void sendPulse(bool state, uint32_t micros);
};

/**
 * @}
 */

#endif // RTS_REMOTE_HPP