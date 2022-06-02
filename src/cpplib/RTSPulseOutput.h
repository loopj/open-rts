#pragma once

#include "rts_pulse_output.h"

class RTSPulseOutput : protected rts_pulse_output {
  public:
    ~RTSPulseOutput() {
        // TODO: Fix segfault
        // rts_pulse_output_close(this);
    }

    void enable() {
        rts_pulse_output_enable(this);
    }

    void disable() {
        rts_pulse_output_disable(this);
    }

    void sendPulse(bool state, uint32_t micros) {
        rts_pulse_output_send_pulse(this, state, micros);
    }

  protected:
    RTSPulseOutput() {
        rts_pulse_output::send_pulse = nullptr;
        rts_pulse_output::enable = nullptr;
        rts_pulse_output::disable = nullptr;
    }

  friend class RTSRemote;
};