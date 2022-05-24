#ifndef RTS_FRAME_BUILDER_H
#define RTS_FRAME_BUILDER_H

#include "rts_frame.h"
#include "rts_timings.h"

#include <stdint.h>

/**
 * Assembles pulses received via #rts_frame_builder_handle_pulse, into a complete
 * rts_frame, and delivers them to the user-provided callback.
 *
 * This class will fire the configured callback _every time_ a
 * valid RTS frame is received. It does not perform any sort of deduplication,
 * or validation of remote addresses or rolling codes, which makes it ideal
 * for building a "frame sniffer", "remote sniffer", or any kind of promiscuous
 * receiver.
 *
 * An rts_frame_builder can be attached to an rts_pulse_source (eg. a GPIO or
 * radio) with rts_pulse_source_attach to observe pulses and build
 * frames automatically.
 */
struct rts_frame_builder {
    /// Timings to use for generating pulses
    struct rts_timings *timings;

    /// The timing tolerance to use when processing pulses. Defaults to
    /// `timings->symbol / 2` when calling rts_frame_builder_init
    uint16_t tolerance;

    /// User provided frame callback
    void (*callback)(struct rts_frame *frame, uint8_t count, uint32_t duration,
                     void *user_data);

    /// Additional user data to supply whenever callback is called
    void *callback_user_data;

    //
    // Internal frame assembly state
    //

    // Frame builder state
    uint8_t mode;

    // The frame currently being assembled
    uint8_t bytes[RTS_FRAME_BYTES];

    // The number of bits we've assembled so far
    uint8_t bits;

    // Are we half way through receiving a bit
    bool mid_bit : 1;

    // Keep track of previous manchester symbol
    bool prev_symbol : 1;

    // Check if this is the first data pulse
    uint8_t first_data_pulse;

    // The number of preamble pulses received while assembling this frame
    uint8_t preambles;

    // The last complete frame we assembled, used to detect repeat frames
    uint8_t last_bytes[RTS_FRAME_BYTES];

    // How many times have we seen this frame repeated
    uint8_t frame_repeat_count;

    // When did we first see this frame
    uint32_t frame_first_seen;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize an rts_frame_builder with the specified timings.
 *
 * @relates rts_frame_builder
 *
 * @param builder the rts_frame_builder struct to initialize
 * @param timings the rts_timings struct to use for pulse decoding
 */
void rts_frame_builder_init(struct rts_frame_builder *builder,
                            struct rts_timings *timings);

/**
 * Inform the frame builder about a new pulse.
 * This is typically called from an rts_pulse_source that has been attached
 * using rts_pulse_source_attach.
 *
 * @relates rts_frame_builder
 *
 * @param builder the rts_frame_builder struct
 * @param state boolean pulse logic state, true = HIGH, false = LOW
 * @param micros the time the pulse was in this state, in microseconds
 */
void rts_frame_builder_handle_pulse(struct rts_frame_builder *builder,
                                    bool state, uint32_t micros);

/**
 * Set a callback to call when new complete frames are received
 *
 * @relates rts_frame_builder
 *
 * @param builder the rts_frame_builder struct
 * @param callback the callback to fire
 * @param user_data optional custom user data pointer, will be included as
 *                  the last parameter when callback is fired
 */
void rts_frame_builder_set_callback(struct rts_frame_builder *builder,
                                    void (*callback)(struct rts_frame *frame,
                                                     uint8_t count,
                                                     uint32_t duration,
                                                     void *user_data),
                                    void *user_data);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_FRAME_BUILDER_H