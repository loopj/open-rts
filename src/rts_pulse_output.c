#include "rts_pulse_output.h"

void rts_pulse_output_enable(rts_pulse_output_t *pulse_output) {
    if(!pulse_output->enable_fn) {
        // TODO: Log a warning/error
        return;
    }

    pulse_output->enable_fn(pulse_output);
}

void rts_pulse_output_disable(rts_pulse_output_t *pulse_output) {
    if(!pulse_output->disable_fn) {
        // TODO: Log a warning/error
        return;
    }

    pulse_output->disable_fn(pulse_output);
}

void rts_pulse_output_send_pulse(rts_pulse_output_t *pulse_output, bool state, uint32_t micros) {
    if(!pulse_output->send_pulse_fn) {
        // TODO: Log a warning/error
        return;
    }

    pulse_output->send_pulse_fn(pulse_output, state, micros);
}