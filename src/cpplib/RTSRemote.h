#pragma once

#include "rts_remote.h"

#include "RTSFrame.h"
#include "RTSPulseOutput.h"
#include "RTSRemoteStore.h"

class RTSRemote : public rts_remote {
  public:
    RTSRemote(RTSPulseOutput *output, RTSRemoteStore *store=nullptr, rts_timings *timings=RTS_TIMINGS_DEFAULT) {
        this->remote_store = store;
        this->pulse_output = output;
        this->timings = timings;
    }

    void sendCommand(uint32_t address, rts_command command, bool repeated=false) {
        rts_remote_send_command(this, address, command, repeated);

    }

    void sendFrame(RTSFrame *frame, bool repeated=false) {
        rts_remote_send_frame(this, frame, repeated);
    }

    void sendPulse(bool state, uint32_t micros) {
        rts_pulse_output_send_pulse(pulse_output, state, micros);
    }
};