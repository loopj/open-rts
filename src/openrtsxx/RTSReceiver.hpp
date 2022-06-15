#ifndef RTS_RECEIVER_HPP
#define RTS_RECEIVER_HPP

#include "openrts/rts_receiver.h"

#include "RTSFrame.hpp"
#include "RTSPulseSource.hpp"
#include "RTSRemoteStore.hpp"

/**
 * @file
 */

/**
 * @addtogroup openrtsxx
 * @{
 */

/**
 * Simulates a physical RTS receiver device, such as a shade or drapery motor.
 *
 * It connects an RTSPulseSource (eg. a GPIO or radio) to an internal
 * RTSFrameBuilder and adds common receiver functionality such as frame
 * de-duplication, remote pairing, and rolling code validation.
 *
 * De-duplicated frame "events" such as "remote button pressed" and "remote
 * button held" are sent to the event callback you attach with
 * RTSReceiver::setFrameCallback.
 *
 * Paired remotes and rolling codes can be persisted by providing a
 * RTSRemoteStore backend (eg. ESP32's non-volatile storage, Arduino's EEPROM,
 * or something custom if you'd prefer).
 *
 * Receivers can be in one of three modes: "off", "programming" or "command".
 *
 * In "off" mode, the receiver will not process any commands from remotes. To
 * re-enable processing of commands, you'll need to call RTSReceiver::setMode.
 * Typically you'll want to call this when the user presses a physical button
 * on the receiver, as on real RTS devices.
 *
 * In "programming" mode, the receiver will process pairing/unpairing commands
 * from remotes (Prog button pressed), and also process "RTS Off" commands from
 * remotes (My+Up+Down buttons pressed and held).
 *
 * In "command" mode, the receiver will process regular RTS frame events with
 * rolling code validation, and handle certain special events such as allowing
 * a paired remote to enter "programming" mode by pressing and holding "Prog".
 */
class RTSReceiver : protected rts_receiver
{
  public:
    /**
     * Frame event callback function type.
     *
     * @param event the rts_recevier_event that was detected, eg
     *              RTS_RECEIVER_EVENT_PRESS, RTS_RECEIVER_EVENT_HOLD, etc
     * @param frame the RTSFrame that was detected
     * @param userData custom userdata provided to
     *                 RTSReceiver::setFrameCallback, if any
     */
    typedef void (*FrameCallback)(enum rts_receiver_event event,
                                  RTSFrame *frame, void *userData);

    /**
     * Mode change callback function type.
     *
     * @param mode the mode the receiver changed to, eg
     *             RTS_RECEIVER_MODE_PROGRAMMING, RTS_RECEIVER_MODE_COMMAND, etc
     * @param userData custom userdata provided to RTSReceiver::setModeCallback,
     *                 if any
     */
    typedef void (*ModeCallback)(enum rts_receiver_mode mode, void *userData);

    /**
     * Construct an RTSReceiver.
     *
     * @param pulseSource the RTSPulseSource to receive pulses from
     * @param remoteStore the RTSRemoteStore to persist paired remotes to
     */
    RTSReceiver(RTSPulseSource *pulseSource, RTSRemoteStore *remoteStore);

    /**
     * Set a callback function to call when new receiver events are received.
     *
     * @param callback the callback function to call when new frame events are
     *                 received. Frame events are fired after RTS frames are parsed
     *                 and deduplicated.
     * @param userData optional user_data pointer to pass to every callback.
     */
    void setFrameCallback(FrameCallback callback, void *userData = nullptr);

    /**
     * Set a callback function to call when the receiver mode changes.
     *
     * @param callback the callback function to call when the mode changes
     * @param userData optional user_data pointer top pass to every callback
     */
    void setModeCallback(ModeCallback callback, void *userData = nullptr);

    /**
     * Change the receiver mode. Receivers can be either "off", in "programming"
     * mode or "command" mode.
     *
     * @param mode the rts_receiver_mode to change to
     */
    void setMode(enum rts_receiver_mode mode);

    /**
     * Convenience function to forget all paired remotes by clearing the
     * receiver's RTSRemoteStore.
     */
    void forgetAllRemotes();

    /**
     * Instruct the receiver's RTSPulseSource to check for new pulse data,
     * should be called every loop() if the pulse source does not keep itself
     * updated (eg. using interrupts).
     */
    void update();

  private:
    // Wrapper function to convert rts_receiver frame callbacks
    static void frameCallbackWrapper(enum rts_receiver_event event,
                                     rts_frame *frame, void *userData);

    // Wrapper function to convert rts_receiver mode callbacks
    static void modeCallbackWrapper(enum rts_receiver_mode mode,
                                    void *userData);

    // User provided frame callback
    FrameCallback frameCallback = nullptr;
    void *frameCallbackUserData = nullptr;

    // User provided mode callback
    ModeCallback modeCallback  = nullptr;
    void *modeCallbackUserData = nullptr;
};

/**
 * @}
 */

#endif // RTS_RECEIVER_HPP