#ifndef RTS_PULSE_OUTPUT_CPP_H
#define RTS_PULSE_OUTPUT_CPP_H

#include "RTSFrameBuilder.h"

#include "rts_pulse_source.h"

class RTSPulseSource : protected rts_pulse_source
{
  public:
    ~RTSPulseSource()
    {
        rts_pulse_source_close(this);
    }

    void enable()
    {
        rts_pulse_source_enable(this);
    }

    void disable()
    {
        rts_pulse_source_disable(this);
    }

    void update()
    {
        rts_pulse_source_update(this);
    }

    void attach(RTSFrameBuilder *frameBuilder)
    {
        rts_pulse_source_attach(this, frameBuilder);
    }

  protected:
    RTSPulseSource()
    {
        rts_pulse_source::enable  = nullptr;
        rts_pulse_source::disable = nullptr;
        rts_pulse_source::update  = nullptr;
        rts_pulse_source::close   = nullptr;
    }

    friend class RTSReceiver;
};

#endif // RTS_PULSE_OUTPUT_CPP_H