#ifndef RTS_PULSE_OUTPUT_ESPIDF_GPIO_H
#define RTS_PULSE_OUTPUT_ESPIDF_GPIO_H

#include "rts_pulse_output.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize an rts_pulse_output which sends pulses to the specified
 * ESP-IDF GPIO pin.
 *
 * @note Only available on ESP8266/ESP32 devices
 *
 * @relates rts_pulse_output
 *
 * @param pulse_output the rts_pulse_output struct to initialize
 * @param data_pin the GPIO pin number to output pulses to
 */
void rts_pulse_output_init_espidf_gpio(struct rts_pulse_output *pulse_output,
                                       uint8_t data_pin);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_PULSE_OUTPUT_ESPIDF_GPIO_H