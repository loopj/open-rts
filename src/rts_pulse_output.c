#include "rts_pulse_output.h"

void rts_pulse_output_enable(struct rts_pulse_output *pulse_output)
{
    if (!pulse_output->enable) {
        // TODO: Log a warning/error
        return;
    }

    pulse_output->enable(pulse_output);
}

void rts_pulse_output_disable(struct rts_pulse_output *pulse_output)
{
    if (!pulse_output->disable) {
        // TODO: Log a warning/error
        return;
    }

    pulse_output->disable(pulse_output);
}

void rts_pulse_output_send_pulse(struct rts_pulse_output *pulse_output,
                                 bool state, uint32_t micros)
{
    if (!pulse_output->send_pulse) {
        // TODO: Log a warning/error
        return;
    }

    pulse_output->send_pulse(pulse_output, state, micros);
}