#include "config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSFrameBuilder.hpp"

RTSFrameBuilder::RTSFrameBuilder(rts_timings *timings)
{
    rts_frame_builder_init(this, timings);
}

void RTSFrameBuilder::setFrameCallback(FrameCallback callback, void *userData)
{
    this->frameCallback         = callback;
    this->frameCallbackUserData = userData;

    rts_frame_builder_set_callback(this, callbackWrapper, this);
}

void RTSFrameBuilder::handlePulse(bool state, uint32_t micros)
{
    rts_frame_builder_handle_pulse(this, state, micros);
}

void RTSFrameBuilder::callbackWrapper(rts_frame *frame, uint8_t repeatCount,
                                      uint32_t repeatDuration, void *userData)
{
    RTSFrameBuilder *inst = (RTSFrameBuilder *)userData;

    RTSFrame convertedFrame(frame);
    inst->frameCallback(&convertedFrame, repeatCount, repeatDuration,
                        inst->frameCallbackUserData);
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS