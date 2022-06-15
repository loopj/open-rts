#ifndef RTS_FRAME_BUILDER_HPP
#define RTS_FRAME_BUILDER_HPP

#include "openrts/rts_frame_builder.h"

#include "RTSFrame.hpp"

/**
 * @file
 */

/**
 * @addtogroup openrtsxx
 * @{
 */

/**
 * Assembles pulses received via RTSFrameBuilder::handlePulse, into a
 * complete RTSFrame, and delivers them to the user-provided callback.
 *
 * This class will fire the callback set by RTSFrameBuilder::setFrameCallback
 * _every time_ a valid RTS frame is received. It does not perform any sort of
 * deduplication, or validation of remote addresses or rolling codes, which
 * makes it ideal for building a "frame sniffer", "remote sniffer", or any kind
 * of promiscuous receiver.
 *
 * An RTSFrameBuilder can be attached to an RTSPulseSrouce (eg. a GPIO or
 * radio) with RTSPulseSource::attach to observe pulses and build
 * frames automatically.
 */
class RTSFrameBuilder : public rts_frame_builder
{
  public:
    /**
     * Frame callback function type.
     *
     * @param frame the RTSFrame that was detected.
     * @param repeatCount number of times this exact frame was repeated
     * @param repeatDuration how long since we first saw this repeated frame, in milliseconds
     * @param userData custom userdata provided to RTSFrameBuilder::onFrame, if any
     */
    typedef void (*FrameCallback)(RTSFrame *frame, uint8_t repeatCount,
                                  uint32_t repeatDuration, void *userData);

    /**
     * Construct an RTSFrameBuilder with the specified timings.
     *
     * @param timings the rts_timings struct to use for pulse decoding
     */
    RTSFrameBuilder(rts_timings *timings = RTS_TIMINGS_DEFAULT);

    /**
     * Set a callback to call when new complete frames are received
     *
     * @param callback the callback to fire
     * @param userData optional custom user data pointer, will be included as
     *                 the last parameter when callback is fired
     */
    void setFrameCallback(FrameCallback callback, void *userData = nullptr);

    /**
     * Inform the frame builder about a new pulse.
     * This is typically called from an RTSPulseSource that has been attached
     * using RTSPulseSource::attach.
     *
     * @param state boolean pulse logic state, true = HIGH, false = LOW
     * @param micros the time the pulse was in this state, in microseconds
     */
    void handlePulse(bool state, uint32_t micros);

  private:
    // Wrapper function to convert rts_frame_builder callbacks
    static void callbackWrapper(rts_frame *frame, uint8_t repeatCount,
                                uint32_t repeatDuration, void *userData);

    // User provided frame callback
    FrameCallback frameCallback = nullptr;
    void *frameCallbackUserData = nullptr;

    friend class RTSPulseSource;
};

/**
 * @}
 */

#endif // RTS_FRAME_BUILDER_HPP