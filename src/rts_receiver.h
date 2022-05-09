#include "rts_frame.h"
#include "rts_frame_builder.h"
#include "rts_pulse_source.h"
#include "rts_remote_store.h"

#define RTS_RECEIVER_HOLD_DURATION                2000
#define RTS_RECEIVER_HOLD_2_DURATION              4000
#define RTS_RECEIVER_HOLD_3_DURATION              6000
#define RTS_RECEIVER_DEFAULT_ROLLING_CODE_WINDOW  128
#define RTS_RECEIVER_PROGRAMMING_MODE_TIMEOUT     120000

typedef enum {
    RTS_RECEIVER_EVENT_NONE,
    RTS_RECEIVER_EVENT_PRESS,
    RTS_RECEIVER_EVENT_HOLD,
    RTS_RECEIVER_EVENT_HOLD_2,
    RTS_RECEIVER_EVENT_HOLD_3,
} rts_receiver_event_t;

typedef enum {
    RTS_RECEIVER_MODE_OFF,
    RTS_RECEIVER_MODE_PROGRAMMING,
    RTS_RECEIVER_MODE_COMMAND,
} rts_receiver_mode_t;

typedef void (*rts_receiver_event_callback_t)(rts_receiver_event_t event, rts_frame_t *frame, void *user_data);
typedef void (*rts_receiver_mode_change_callback_t)(rts_receiver_mode_t mode, void *user_data);

typedef struct rts_receiver_t {
    rts_frame_builder_t frame_builder;

    rts_pulse_source_t *pulse_source;
    rts_remote_store_t *remote_store;

    rts_receiver_mode_t mode;
    uint32_t mode_last_changed;
    rts_receiver_event_t event_fired;
    uint8_t rolling_code_window;

    rts_receiver_event_callback_t event_callback;
    void *event_callback_user_data;
    rts_receiver_mode_change_callback_t mode_change_callback;
    void *mode_change_callback_user_data;
} rts_receiver_t;

void rts_receiver_init(rts_receiver_t *receiver, rts_pulse_source_t *pulse_source, rts_remote_store_t *remote_store);
void rts_receiver_set_event_callback(rts_receiver_t *receiver, rts_receiver_event_callback_t callback, void *user_data);
void rts_receiver_set_mode_change_callback(rts_receiver_t *receiver, rts_receiver_mode_change_callback_t callbacl, void *user_data);
void rts_receiver_set_mode(rts_receiver_t *receiver, rts_receiver_mode_t mode);
void rts_receiver_forget_all_remotes(rts_receiver_t *receiver);
void rts_receiver_update(rts_receiver_t *receiver);