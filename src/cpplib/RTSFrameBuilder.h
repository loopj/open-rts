#pragma once

#include "RTSFrame.h"
#include "rts_frame_builder.h"

class RTSFrameBuilder : protected rts_frame_builder {
  public:
    typedef void (*FrameCallback)(RTSFrame *frame, uint8_t repeatCount, uint32_t repeatDuration, void *userData);

    RTSFrameBuilder(rts_timings *timings=RTS_TIMINGS_DEFAULT) {
        rts_frame_builder_init(this, timings);
    }

    void setFrameCallback(FrameCallback callback, void *userData) {
        this->frameCallback = callback;
        this->frameCallbackUserData = userData;

        rts_frame_builder_set_callback(this, [](rts_frame *frame, uint8_t repeat_count, uint32_t repeat_duration, void *user_data) {
            RTSFrameBuilder *inst = (RTSFrameBuilder *)user_data;

            // Convert rts_frame_t to RTSFrame
            // TODO: Copy constructor?
            RTSFrame convertedFrame(frame->command, frame->rolling_code, frame->remote_address);
            convertedFrame.encryption_key = frame->encryption_key;

            inst->frameCallback(&convertedFrame, repeat_count, repeat_duration, inst->frameCallbackUserData);
        }, this);
    }

    void handlePulse(bool state, uint32_t micros) {
        rts_frame_builder_handle_pulse(this, state, micros);
    }

  private:
    FrameCallback frameCallback = nullptr;
    void *frameCallbackUserData = nullptr;
};