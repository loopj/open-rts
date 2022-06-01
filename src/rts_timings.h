/// @file

#ifndef RTS_TIMINGS_H
#define RTS_TIMINGS_H

#include <stdint.h>

/**
 * Timing definitions for encoding and decoding frames to pulses.
 *
 * You can provide your own custom timings, but it is most common to use
 * the predefined timings provided in the RTS_TIMINGS_DEFAULT global.
 *
 * RTS remotes will send a wakeup pulse, followed by a series of frames,
 * separated by an inter-frame sleep pulse.
 *
 * RTS frames are encoded by sending a series of preambles, followed by a
 * software sync, then a series of manchester-encoded data symbols.
 */
struct rts_timings {
    /// Width of the high part of a "wakeup pulse", in microseconds
    uint16_t wakeup_high;

    /// Width of the low part of a "wakeup pulse", in microseconds
    uint16_t wakeup_low;

    /// Width of the high part of a "preamble", in microseconds
    uint16_t preamble_high;

    /// Width of the low part of a "preamble", in microseconds
    uint16_t preamble_low;

    /// Width of the high part of a "software sync", in microseconds
    uint16_t sync_high;

    /// Width of the low part of a "software sync", in microseconds
    uint16_t sync_low;

    /// Width of a data symbol (either high or low), in microseconds
    uint16_t symbol;

    /// Width of an inter-frame sleep (low), in microseconds
    uint16_t frame_sleep;
};

/// Timings as measured from a physical Situio5 remote
extern struct rts_timings RTS_TIMINGS_SITUO5;

/// Default timings, suitable for most application
extern struct rts_timings *RTS_TIMINGS_DEFAULT;

#endif // RTS_TIMINGS_H