#include "rts_pulse_source.h"

void rts_pulse_source_enable(rts_pulse_source_t *pulse_source) {
    if(!pulse_source->enable_fn) {
        // TODO: Log a warning/error
        return;
    }
    
    pulse_source->enable_fn(pulse_source);
}

void rts_pulse_source_disable(rts_pulse_source_t *pulse_source) {
    if(!pulse_source->disable_fn) {
        // TODO: Log a warning/error
        return;
    }

    pulse_source->disable_fn(pulse_source);
}

void rts_pulse_source_update(rts_pulse_source_t *pulse_source) {
    if(!pulse_source->update_fn) {
        // TODO: Log a warning/error
        return;
    }

    pulse_source->update_fn(pulse_source);
}