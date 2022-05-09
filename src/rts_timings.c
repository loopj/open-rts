#include "rts_timings.h"

// Pre-defined RTS protocol timings
rts_timings_t RTS_TIMINGS_SITUO5 =
{
    10568,      // wakeup_high
    7072,       // wakeup_low
    2585,       // preamble_high
    2436,       // preamble_low
    4898,       // sync_high
    644,        // sync_low
    644,        // symbol
    26838,      // frame_sleep
};

rts_timings_t *RTS_TIMINGS_DEFAULT = &RTS_TIMINGS_SITUO5;