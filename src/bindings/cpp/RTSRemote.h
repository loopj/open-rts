#ifndef RTS_REMOTE_CPP_H
#define RTS_REMOTE_CPP_H

#include "rts_remote.h"

#include "RTSFrame.h"
#include "RTSPulseOutput.h"
#include "RTSRemoteStore.h"

class RTSRemote : public rts_remote
{
  public:
    RTSRemote(RTSPulseOutput *output, RTSRemoteStore *store = nullptr,
              rts_timings *timings = RTS_TIMINGS_DEFAULT);

    void sendCommand(uint32_t address, rts_command command,
                     bool repeated = false);
    void sendFrame(RTSFrame *frame, bool repeated = false);
    void sendPulse(bool state, uint32_t micros);
};

#endif // RTS_REMOTE_CPP_H