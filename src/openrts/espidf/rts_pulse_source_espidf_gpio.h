#ifndef RTS_PULSE_SOURCE_ESPIDF_GPIO_H
#define RTS_PULSE_SOURCE_ESPIDF_GPIO_H

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
 * ESP-IDF GPIO pin.
 *
 * @note Only available on ESP8266/ESP32 devices
 *
 * @relates rts_pulse_source
 *
 * @param pulse_source the rts_pulse_source struct to initialize
 * @param data_pin the GPIO pin to monitor
 */
void rts_pulse_source_init_espidf_gpio(struct rts_pulse_source *pulse_source,
                                       uint8_t data_pin);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @}
 */

#endif // RTS_PULSE_SOURCE_ESPIDF_GPIO_H