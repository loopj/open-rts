/**
 * @file
 * @addtogroup openrts
 *  @{
 */

#ifndef RTS_RECEIVER_H
#define RTS_RECEIVER_H

#include "rts_frame.h"
#include "rts_frame_builder.h"
#include "rts_pulse_source.h"
#include "rts_remote_store.h"

/**
 * De-duplicated "frame" events.
 */
enum rts_receiver_event {
    RTS_RECEIVER_EVENT_NONE,    ///< No event detected.
    RTS_RECEIVER_EVENT_PRESS,   ///< "Press" event detected, fired on first frame
    RTS_RECEIVER_EVENT_HOLD,    ///< "Hold" event detected, fired after 2s of repeats
    RTS_RECEIVER_EVENT_HOLD_2,  ///< "2x Hold" event detected, fired after 4s of repeats
    RTS_RECEIVER_EVENT_HOLD_3,  ///< "3x Hold" event detected, fired after 6s of repeats
};

/**
 * Receiver modes.
 */
enum rts_receiver_mode {
    RTS_RECEIVER_MODE_OFF,          ///< The receiver is off, will not process events.
    RTS_RECEIVER_MODE_PROGRAMMING,  ///< The receiver is in programming mode.
    RTS_RECEIVER_MODE_COMMAND,      ///< The receiver is in command mode.
};

/**
 * Simulates a physical RTS receiver device, such as a shade or drapery motor.
 *
 * It connects an rts_pulse_source (eg. a GPIO or radio) to an internal
 * rts_frame_builder and adds common receiver functionality such as frame
 * de-duplication, remote pairing, and rolling code validation.
 *
 * De-duplicated frame "events" such as "remote button pressed" and "remote
 * button held" are sent to the event callback you attach with
 * rts_receiver_set_frame_callback.
 *
 * Paired remotes and rolling codes can be persisted by providing a
 * rts_remote_store backend (eg. ESP32's non-volatile storage, Arduino's EEPROM,
 * or something custom if you'd prefer).
 *
 * Receivers can be in one of three modes: "off", "programming" or "command".
 *
 * In "off" mode, the receiver will not process any commands from remotes. To
 * re-enable processing of commands, you'll need to call
 * rts_receiver_set_mode(). Typically you'll want to call this when the user
 * presses a physical button on the receiver, as on real RTS devices.
 *
 * In "programming" mode, the receiver will process pairing/unpairing commands
 * from remotes (Prog button pressed), and also process "RTS Off" commands from
 * remotes (My+Up+Down buttons pressed and held).
 *
 * In "command" mode, the receiver will process regular RTS frame events with
 * rolling code validation, and handle certain special events such as allowing
 * a paired remote to enter "programming" mode by pressing and holding "Prog".
 */
struct rts_receiver {
    struct rts_frame_builder frame_builder;
    struct rts_pulse_source *pulse_source;
    struct rts_remote_store *remote_store;

    void (*frame_callback)(enum rts_receiver_event event,
                           struct rts_frame *frame, void *user_data);
    void *frame_user_data;

    void (*mode_callback)(enum rts_receiver_mode mode, void *user_data);
    void *mode_user_data;

    uint8_t mode;
    uint32_t mode_last_changed;
    uint8_t event_fired;
    uint8_t rolling_code_window;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize an rts_receiver.
 *
 * @relates rts_receiver
 *
 * @param receiver the rts_receiver struct to initialize
 * @param pulse_source the rts_pulse_source to receive pulses from
 * @param remote_store the rts_remote_store to persist paired remotes to
 */
void rts_receiver_init(struct rts_receiver *receiver,
                       struct rts_pulse_source *pulse_source,
                       struct rts_remote_store *remote_store);

/**
 * Set a callback function to call when new receiver events are received.
 *
 * @relates rts_receiver
 *
 * @param receiver the rts_receiver struct to set callback on
 * @param callback the callback function to call when new frame events are
 *                 received. Frame events are fired after RTS frames are parsed
 *                 and deduplicated.
 * @param user_data optional user_data pointer to pass to every callback. Set
 *                  to NULL if not using.
 */
void rts_receiver_set_frame_callback(struct rts_receiver *receiver,
                                     void (*callback)(enum rts_receiver_event,
                                                      struct rts_frame *frame,
                                                      void *user_data),
                                     void *user_data);

/**
 * Set a callback function to call when the receiver mode changes.
 *
 * @relates rts_receiver
 *
 * @param receiver the rts_receiver struct to set callback on
 * @param callback the callback function to call when the mode changes
 * @param user_data optional user_data pointer top pass to every callback. Set
 *                  to NULL if not using.
 */
void rts_receiver_set_mode_callback(struct rts_receiver *receiver,
                                    void (*callback)(enum rts_receiver_mode,
                                                     void *user_data),
                                    void *user_data);

/**
 * Change the receiver mode. Receivers can be either "off", in "programming"
 * mode or "command" mode.
 *
 * @relates rts_receiver
 *
 * @param receiver the rts_receiver struct to change the mode of
 * @param mode the rts_receiver_mode to change to
 */
void rts_receiver_set_mode(struct rts_receiver *receiver, uint8_t mode);

/**
 * Convenience function to forget all paired remotes by clearing the receiver's
 * rts_remote_store.
 *
 * @relates rts_receiver
 *
 * @param receiver the rts_receiver struct to forget remotes for
 */
void rts_receiver_forget_all_remotes(struct rts_receiver *receiver);

/**
 * Instruct the receiver's rts_pulse_source to check for new pulse data,
 * should be called every loop() if the pulse source does not keep itself
 * updated (eg. using interrupts).
 *
 * @relates rts_receiver
 *
 * @param receiver the rts_receiver struct to update
 */
void rts_receiver_update(struct rts_receiver *receiver);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_RECEIVER_H

/// @}