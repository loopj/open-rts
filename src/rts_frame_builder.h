#pragma once

#include <stdint.h>

#include "rts_frame.h"
#include "rts_timings.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTS_FRAME_BUILDER_AWAITING_SYNC     0
#define RTS_FRAME_BUILDER_RECEIVING_DATA    1
#define RTS_FRAME_BUILDER_DEFAULT_TIMING    RTS_TIMINGS_SITUO5

typedef void (*rts_frame_callback_t)(rts_frame_t *frame, uint8_t repeat_count, uint32_t repeat_duration, void *user_data);

typedef struct rts_frame_builder_t {
    // Timings to use for generating pulses
    rts_timings_t *timings;

    // The timing tolerance to use when processing pulses
    uint16_t timing_tolerance;


    //
    // Frame assembly state (TODO: Private)
    //

    // Frame builder state
    uint8_t mode;

    // The frame currently being assembled
    uint8_t bytes[RTS_FRAME_BYTES];

    // The number of bits we've assembled so far
    uint8_t bit_count;

    // Are we half way through receiving a bit
    bool mid_bit : 1;

    // Keep track of previous manchester symbol
    bool prev_symbol : 1;

    // Check if this is the first data pulse
    uint8_t first_data_pulse;

    // The number of preamble pulses received while assembling this frame
    uint8_t preamble_count;


    //
    // Callbacks and events
    //

    // The last complete frame we assembled, used to detect repeat frames
    uint8_t last_bytes[RTS_FRAME_BYTES];

    // How many times have we seen this frame repeated
    uint8_t frame_repeat_count;

    // When did we first see this frame
    uint32_t frame_first_seen;

    // User provided frame callback
    rts_frame_callback_t callback;
    void *callback_user_data;

} rts_frame_builder_t;

void rts_frame_builder_init(rts_frame_builder_t *builder, rts_timings_t *timings);
void rts_frame_builder_handle_pulse(rts_frame_builder_t *builder, bool state, uint32_t micros);
void rts_frame_builder_set_callback(rts_frame_builder_t *builder, rts_frame_callback_t callback, void *user_data);

#ifdef __cplusplus
} // extern "C"
#endif