#ifndef RTS_FRAME_BUILDER_CPP_H
#define RTS_FRAME_BUILDER_CPP_H

#include "RTSFrame.h"

#include "rts_frame_builder.h"

class RTSFrameBuilder : protected rts_frame_builder
{
  public:
    typedef void (*FrameCallback)(RTSFrame *frame, uint8_t repeatCount,
                                  uint32_t repeatDuration, void *userData);

    RTSFrameBuilder(rts_timings *timings = RTS_TIMINGS_DEFAULT)
    {
        rts_frame_builder_init(this, timings);
    }

    void setFrameCallback(FrameCallback callback, void *userData = nullptr)
    {
        this->frameCallback         = callback;
        this->frameCallbackUserData = userData;

        rts_frame_builder_set_callback(
            this,
            [](rts_frame *frame, uint8_t repeatCount, uint32_t repeatDuration,
               void *userData) {
                RTSFrameBuilder *inst = (RTSFrameBuilder *)userData;

                RTSFrame convertedFrame(frame->command, frame->rolling_code,
                                        frame->remote_address);
                convertedFrame.encryption_key = frame->encryption_key;
                inst->frameCallback(&convertedFrame, repeatCount,
                                    repeatDuration,
                                    inst->frameCallbackUserData);
            },
            this);
    }

    void handlePulse(bool state, uint32_t micros)
    {
        rts_frame_builder_handle_pulse(this, state, micros);
    }

  private:
    FrameCallback frameCallback = nullptr;
    void *frameCallbackUserData = nullptr;

    friend class RTSPulseSource;
};

#endif // RTS_FRAME_BUILDER_CPP_H