#include "rts_pulse_source.h"

void rts_pulse_source_attach(struct rts_pulse_source *pulse_source,
                             struct rts_frame_builder *frame_builder)
{
    pulse_source->frame_builder = frame_builder;
}

void rts_pulse_source_enable(struct rts_pulse_source *pulse_source)
{
    if (!pulse_source->enable) {
        // TODO: Log a warning/error
        return;
    }

    pulse_source->enable(pulse_source);
}

void rts_pulse_source_disable(struct rts_pulse_source *pulse_source)
{
    if (!pulse_source->disable) {
        // TODO: Log a warning/error
        return;
    }

    pulse_source->disable(pulse_source);
}

void rts_pulse_source_update(struct rts_pulse_source *pulse_source)
{
    if (!pulse_source->update) {
        // TODO: Log a warning/error
        return;
    }

    pulse_source->update(pulse_source);
}