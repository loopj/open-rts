#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rts_pulse_output_t {
    void (*enable_fn)(struct rts_pulse_output_t *pulse_output);
    void (*disable_fn)(struct rts_pulse_output_t *pulse_output);
    void (*send_pulse_fn)(struct rts_pulse_output_t *pulse_output, bool state, uint32_t micros);

    union {
        void *user_data_ptr;
        int user_data_int;
    };
} rts_pulse_output_t;

void rts_pulse_output_enable(rts_pulse_output_t *pulse_output);
void rts_pulse_output_disable(rts_pulse_output_t *pulse_output);
void rts_pulse_output_send_pulse(rts_pulse_output_t *pulse_output, bool state, uint32_t micros);

#ifdef __cplusplus
} // extern "C"
#endif