#ifndef RTS_REMOTE_H
#define RTS_REMOTE_H

#include "rts_frame.h"
#include "rts_pulse_output.h"
#include "rts_remote_store.h"
#include "rts_timings.h"

#include <stdint.h>

/**
 * @file
 */

/**
 * @addtogroup openrts
 * @{
 */

/**
 * Simulates a physical RTS remote control.
 *
 * It takes RTS commands (button presses), converts them into a series of
 * pulses, then outputs those pulses to a rts_pulse_output (eg. a GPIO or radio).
 *
 * Remote rolling codes can be persisted by providing a rts_remote_store backend
 * (eg. ESP32's non-volatile storage, or Arduino's EEPROM).
 */
struct rts_remote {
    struct rts_pulse_output *pulse_output;
    struct rts_remote_store *remote_store;
    struct rts_timings *timings;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the rts_remote struct
 *
 * @relates rts_remote
 *
 * @param remote the rts_remote struct to initialize
 * @param pulse_output where to send pulses to
 * @param remote_store where to get/set remote rolling codes
 * @param timings the rts_timings struct to use for pulse encoding
 */
void rts_remote_init(struct rts_remote *remote,
                     struct rts_pulse_output *pulse_output,
                     struct rts_remote_store *remote_store,
                     struct rts_timings *timings);

/**
 * Send a "button press" command.
 *
 * This is the simplest way to use an rts_remote, which automatically creates
 * an rts_frame struct under the hood, and handles the incrementing of rolling
 * codes in the internal rts_remote_store.
 *
 * The generated rts_frame is passed to rts_remote_send_frame.
 *
 * @relates rts_remote
 *
 * @param remote the rts_remote struct
 * @param address the remote address to send from
 * @param command the rts command to send (see rts_command enum)
 * @param repeated is this a "repeated" command, eg. from a button being held
 *                 down? If so we won't increment the remote's rolling code
 */
void rts_remote_send_command(struct rts_remote *remote, uint32_t address,
                             enum rts_command command, bool repeated);

/**
 * Send an RTS frame.
 *
 * This function converts the provided rts_frame into a series of pulses, which
 * are passed along to the internal rts_pulse_output by rts_remote_send_pulse.
 *
 * @relates rts_remote
 *
 * @param remote the rts_remote struct
 * @param frame the rts_frame to send
 * @param repeated is this a "repeated" command, eg. from a button being held
 *                 down? If so we won't increment the remote's rolling code
 */
void rts_remote_send_frame(struct rts_remote *remote, struct rts_frame *frame,
                           bool repeated);

/**
 * Send a single pulse to the internal rts_pulse_output.
 *
 * @relates rts_remote
 *
 * @param remote the rts_remote struct
 * @param state boolean pulse logic state, true = HIGH, false = LOW
 * @param micros how long to set the pulse to this state, in microseconds
 */
void rts_remote_send_pulse(struct rts_remote *remote, bool state,
                           uint32_t micros);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @}
 */

#endif // RTS_REMOTE_H