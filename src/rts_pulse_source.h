#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "rts_frame_builder.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rts_pulse_source_t {
    rts_frame_builder_t *frame_builder;

    void (*enable_fn)(struct rts_pulse_source_t *pulse_source);
    void (*disable_fn)(struct rts_pulse_source_t *pulse_source);
    void (*update_fn)(struct rts_pulse_source_t *pulse_source);

    union {
        void *user_data_ptr;
        int user_data_int;
    };
} rts_pulse_source_t;

void rts_pulse_source_enable(rts_pulse_source_t *pulse_source);
void rts_pulse_source_disable(rts_pulse_source_t *pulse_source);
void rts_pulse_source_update(rts_pulse_source_t *pulse_source);

#ifdef __cplusplus
} // extern "C"
#endif