#ifndef RTS_RECEIVER_H
#define RTS_RECEIVER_H

#include "rts_frame.h"
#include "rts_frame_builder.h"
#include "rts_pulse_source.h"
#include "rts_remote_store.h"

enum rts_receiver_event {
    RTS_RECEIVER_EVENT_NONE,
    RTS_RECEIVER_EVENT_PRESS,
    RTS_RECEIVER_EVENT_HOLD,
    RTS_RECEIVER_EVENT_HOLD_2,
    RTS_RECEIVER_EVENT_HOLD_3,
};

enum rts_receiver_mode {
    RTS_RECEIVER_MODE_OFF,
    RTS_RECEIVER_MODE_PROGRAMMING,
    RTS_RECEIVER_MODE_COMMAND,
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
 * rts_receiver_set_event_callback.
 *
 * Paired remotes and rolling codes can be persisted by providing a
 * rts_remote_store backend (eg. ESP32's non-volatile storage, Arduino's EEPROM,
 * or something custom if you'd prefer).
 */
struct rts_receiver {
    struct rts_frame_builder frame_builder;
    struct rts_pulse_source *pulse_source;
    struct rts_remote_store *remote_store;

    void (*event_callback)(enum rts_receiver_event event,
                           struct rts_frame *frame,
                           void *user_data);
    void *event_user_data;

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

void rts_receiver_init(struct rts_receiver *receiver,
                       struct rts_pulse_source *pulse_source,
                       struct rts_remote_store *remote_store);

void rts_receiver_set_event_callback(struct rts_receiver *receiver,
                                     void (*callback)(enum rts_receiver_event,
                                                      struct rts_frame *frame,
                                                      void *user_data),
                                     void *user_data);

void rts_receiver_set_mode_callback(struct rts_receiver *receiver,
                                    void (*callback)(enum rts_receiver_mode,
                                                     void *user_data),
                                    void *user_data);

void rts_receiver_set_mode(struct rts_receiver *receiver, uint8_t mode);

void rts_receiver_forget_all_remotes(struct rts_receiver *receiver);

void rts_receiver_update(struct rts_receiver *receiver);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_RECEIVER_H