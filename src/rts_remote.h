#pragma once

#include <stdint.h>

#include "rts_command.h"
#include "rts_frame.h"
#include "rts_pulse_output.h"
#include "rts_remote_store.h"
#include "rts_timings.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTS_REMOTE_INITIAL_PREAMBLE_COUNT   2
#define RTS_REMOTE_REPEAT_PREAMBLE_COUNT    7
#define RTS_REMOTE_DEFAULT_TIMING           RTS_TIMINGS_SITUO5

typedef struct rts_remote_t {
    // Interface to use for outputting pulses, eg. a GPIO
    rts_pulse_output_t *pulse_output;

    // Rolling code storage
    rts_remote_store_t *remote_store;

    // Timings to use for generating pulses
    rts_timings_t *timings;
} rts_remote_t;

// void rts_remote_init(rts_remote_t *remote);
void rts_remote_send_command(rts_remote_t *remote, uint32_t address, rts_command_t command, bool repeated);
void rts_remote_send_frame(rts_remote_t *remote, rts_frame_t *frame, bool repeated);
void rts_remote_send_pulse(rts_remote_t *remote, bool state, uint32_t micros);

#ifdef __cplusplus
} // extern "C"
#endif