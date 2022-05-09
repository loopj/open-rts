#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rts_timings_t {
    uint16_t wakeup_high;
    uint16_t wakeup_low;
    uint16_t preamble_high;
    uint16_t preamble_low;
    uint16_t sync_high;
    uint16_t sync_low;
    uint16_t symbol;
    uint16_t frame_sleep;
} rts_timings_t;

extern rts_timings_t  RTS_TIMINGS_SITUO5;
extern rts_timings_t *RTS_TIMINGS_DEFAULT;

#ifdef __cplusplus
} // extern "C"
#endif