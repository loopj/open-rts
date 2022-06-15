#include "openrts/config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSRemote.hpp"

RTSRemote::RTSRemote(RTSPulseOutput *output, RTSRemoteStore *store,
                     rts_timings *timings)
{
    this->pulse_output = output;
    this->remote_store = store;
    this->timings      = timings;
}

void RTSRemote::sendCommand(uint32_t address, rts_command command,
                            bool repeated)
{
    rts_remote_send_command(this, address, command, repeated);
}

void RTSRemote::sendFrame(RTSFrame *frame, bool repeated)
{
    rts_remote_send_frame(this, frame, repeated);
}

void RTSRemote::sendPulse(bool state, uint32_t micros)
{
    rts_pulse_output_send_pulse(this->pulse_output, state, micros);
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS