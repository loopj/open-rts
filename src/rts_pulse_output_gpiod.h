#ifndef RTS_PULSE_OUTPUT_GPIOD_H
#define RTS_PULSE_OUTPUT_GPIOD_H

#include "rts_pulse_output.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize an rts_pulse_output which sends pulses to the specified
 * Linux gpiod device.
 *
 * @note
 *       - Can be enabled on Linux systems by defining the `HAS_GPIOD` macro
 *       - Make sure the libgpiod-dev (>= 1.5) package is available on your
 *         system, eg `sudo apt install libgpiod-dev`
 *       - Don't forget to link libgpiod when building (`-lgpiod`)
 *
 * @relates rts_pulse_output
 *
 * @param pulse_output the rts_pulse_output struct to initialize
 * @param device the device file to use with gpiod, eg "/dev/gpiochip0"
 * @param data_pin the GPIO offset to output to, typically the GPIO pin number
 */
void rts_pulse_output_init_gpiod(struct rts_pulse_output *pulse_output,
                                 char *device, uint8_t data_pin);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_PULSE_OUTPUT_GPIOD_H