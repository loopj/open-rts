#include "config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSPulseSource.h"

RTSPulseSource::~RTSPulseSource()
{
    rts_pulse_source_close(this);
}

void RTSPulseSource::enable()
{
    rts_pulse_source_enable(this);
}

void RTSPulseSource::disable()
{
    rts_pulse_source_disable(this);
}

void RTSPulseSource::update()
{
    rts_pulse_source_update(this);
}

void RTSPulseSource::attach(RTSFrameBuilder *frameBuilder)
{
    rts_pulse_source_attach(this, frameBuilder);
}

RTSPulseSource::RTSPulseSource()
{
    rts_pulse_source::enable  = nullptr;
    rts_pulse_source::disable = nullptr;
    rts_pulse_source::update  = nullptr;
    rts_pulse_source::close   = nullptr;
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS