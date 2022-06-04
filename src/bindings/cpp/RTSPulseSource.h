#pragma once

#include "rts_pulse_source.h"

class RTSPulseSource : protected rts_pulse_source {
  public:
    ~RTSPulseSource() {
        rts_pulse_source_close(this);
    }

    void enable() {
        rts_pulse_source_enable(this);
    }

    void disable() {
        rts_pulse_source_disable(this);
    }

    void update() {
        rts_pulse_source_update(this);
    }

  protected:
    RTSPulseSource() {
        rts_pulse_source::enable = nullptr;
        rts_pulse_source::disable = nullptr;
        rts_pulse_source::update = nullptr;
    }
};