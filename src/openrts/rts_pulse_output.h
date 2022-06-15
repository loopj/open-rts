#ifndef RTS_PULSE_OUTPUT_H
#define RTS_PULSE_OUTPUT_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @file
 */

/**
 * @addtogroup openrts
 * @{
 */

/**
 * Provides an interface for an output of RTS pulses, eg a GPIO or radio.
 *
 * Bundled implementations are provided for Linux/Raspberry Pi gpiod
 * (#rts_pulse_output_init_gpiod) and ESP-IDF GPIO
 * (#rts_pulse_output_init_espidf_gpio).
 *
 * Implementations must define the `enable`, `disable`, and `send_pulse`
 * functions and set the function pointers in the rts_pulse_output struct.
 */
struct rts_pulse_output {
    void (*enable)(struct rts_pulse_output *pulse_output);
    void (*disable)(struct rts_pulse_output *pulse_output);
    void (*send_pulse)(struct rts_pulse_output *pulse_output, bool state,
                       uint32_t micros);
    void (*close)(struct rts_pulse_output *pulse_output);

    union {
        void *user_data_ptr;
        int user_data_int;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enable the pulse output
 *
 * @relates rts_pulse_output
 *
 * @param pulse_output the rts_pulse_output struct to enable
 */
void rts_pulse_output_enable(struct rts_pulse_output *pulse_output);

/**
 * Disable the pulse output
 *
 * @relates rts_pulse_output
 *
 * @param pulse_output the rts_pulse_output struct to disable
 */
void rts_pulse_output_disable(struct rts_pulse_output *pulse_output);

/**
 * Instruct the rts_pulse_output to output a pulse.
 *
 * @relates rts_pulse_output
 *
 * @param pulse_output the rts_pulse_output struct
 * @param state boolean pulse logic state, true = HIGH, false = LOW
 * @param micros the time the pulse was in this state, in microseconds
 */
void rts_pulse_output_send_pulse(struct rts_pulse_output *pulse_output,
                                 bool state, uint32_t micros);

/**
 * Close and free resources allocated via a previous call to
 * rts_pulse_output_init_*()
 *
 * @relates rts_pulse_output
 *
 * @param pulse_output the rts_pulse_output to close
 */
void rts_pulse_output_close(struct rts_pulse_output *pulse_output);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @}
 */

#endif // RTS_PULSE_OUTPUT_H