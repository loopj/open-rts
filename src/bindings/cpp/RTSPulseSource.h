/**
 * @file
 * @addtogroup cpp
 *
 *  @{
 */

#ifndef RTS_PULSE_SOURCE_CPP_H
#define RTS_PULSE_SOURCE_CPP_H

#include "rts_pulse_source.h"

#include "RTSFrameBuilder.h"

/**
 * Provides an interface for a source of RTS pulses, eg a GPIO or radio.
 *
 * Implementations must define the enable, disable, and update
 * functions and set the function pointers in the rts_pulse_source struct.
 *
 * When a new pulse is detected in rts_pulse_source_update, implementations
 * should call rts_frame_builder_handle_pulse on the observer.
 *
 */
class RTSPulseSource : protected rts_pulse_source
{
  public:
    ~RTSPulseSource();

    /**
     * Enable the pulse source
     */
    void enable();

    /**
     * Disable the pulse source
     */
    void disable();

    /**
     * Check for new pulse data. Should be called every loop() if the pulse
     * source does not keep itself updated (eg. using interrupts).
     */
    void update();

    /**
     * Attach an observer
     *
     * @param frameBuilder the RTSFrameBuilder instance observing this source.
     */
    void attach(RTSFrameBuilder *frameBuilder);

  protected:
    RTSPulseSource();

    friend class RTSReceiver;
};

#endif // RTS_PULSE_SOURCE_CPP_H

/// @}