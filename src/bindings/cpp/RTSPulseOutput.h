#ifndef RTS_PULSE_OUTPUT_CPP_H
#define RTS_PULSE_OUTPUT_CPP_H

#include "rts_pulse_output.h"

class RTSPulseOutput : protected rts_pulse_output
{
  public:
    ~RTSPulseOutput();

    void enable();
    void disable();
    void sendPulse(bool state, uint32_t micros);

  protected:
    RTSPulseOutput();

    friend class RTSRemote;
};

#endif // RTS_PULSE_OUTPUT_CPP_H