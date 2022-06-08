#include "config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSPulseOutput.h"

RTSPulseOutput::~RTSPulseOutput()
{
    rts_pulse_output_close(this);
}

void RTSPulseOutput::enable()
{
    rts_pulse_output_enable(this);
}

void RTSPulseOutput::disable()
{
    rts_pulse_output_disable(this);
}

void RTSPulseOutput::sendPulse(bool state, uint32_t micros)
{
    rts_pulse_output_send_pulse(this, state, micros);
}

RTSPulseOutput::RTSPulseOutput()
{
    rts_pulse_output::send_pulse = nullptr;
    rts_pulse_output::enable     = nullptr;
    rts_pulse_output::disable    = nullptr;
    rts_pulse_output::close      = nullptr;
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS