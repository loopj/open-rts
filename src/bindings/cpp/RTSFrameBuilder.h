#ifndef RTS_FRAME_BUILDER_CPP_H
#define RTS_FRAME_BUILDER_CPP_H

#include "rts_frame_builder.h"

#include "RTSFrame.h"

class RTSFrameBuilder : public rts_frame_builder
{
  public:
    typedef void (*FrameCallback)(RTSFrame *frame, uint8_t repeatCount,
                                  uint32_t repeatDuration, void *userData);

    RTSFrameBuilder(rts_timings *timings = RTS_TIMINGS_DEFAULT);

    void setFrameCallback(FrameCallback callback, void *userData = nullptr);
    void handlePulse(bool state, uint32_t micros);

  private:
    static void callbackWrapper(rts_frame *frame, uint8_t repeatCount,
                                uint32_t repeatDuration, void *userData);

    FrameCallback frameCallback = nullptr;
    void *frameCallbackUserData = nullptr;

    friend class RTSPulseSource;
};

#endif // RTS_FRAME_BUILDER_CPP_H