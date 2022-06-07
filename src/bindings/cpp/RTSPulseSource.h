#ifndef RTS_PULSE_SOURCE_CPP_H
#define RTS_PULSE_SOURCE_CPP_H

#include "rts_pulse_source.h"

#include "RTSFrameBuilder.h"

class RTSPulseSource : protected rts_pulse_source
{
  public:
    ~RTSPulseSource();

    void enable();
    void disable();
    void update();
    void attach(RTSFrameBuilder *frameBuilder);

  protected:
    RTSPulseSource();

    friend class RTSReceiver;
};

#endif // RTS_PULSE_SOURCE_CPP_H