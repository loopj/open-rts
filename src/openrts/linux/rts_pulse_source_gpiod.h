#ifndef RTS_PULSE_SOURCE_GPIOD_H
#define RTS_PULSE_SOURCE_GPIOD_H

#include "../rts_pulse_source.h"

/**
 * @file
 */

/**
 * @addtogroup openrts
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize an rts_pulse_source which receives pulses from the specified
 * Linux gpiod device.
 *
 * @note
 *       - Can be enabled on Linux systems by defining the `OPENRTS_HAS_GPIOD`
 *         macro
 *       - Make sure the libgpiod-dev (>= 1.5) package is available on your
 *         system, eg `sudo apt install libgpiod-dev`
 *       - Don't forget to link libgpiod when building (`-lgpiod`)
 *
 * @relates rts_pulse_source
 *
 * @param pulse_source the rts_pulse_source struct to initialize
 * @param device the device file to use with gpiod, eg "/dev/gpiochip0"
 * @param data_pin the GPIO offset to monitor, typically the GPIO pin number
 */
void rts_pulse_source_init_gpiod(struct rts_pulse_source *pulse_source,
                                 char *device, uint8_t data_pin);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @}
 */

#endif // RTS_PULSE_SOURCE_GPIOD_H