#include "rts_receiver.h"

#include "hal.h"

#define HOLD_DURATION               2000
#define HOLD_2_DURATION             4000
#define HOLD_3_DURATION             6000
#define DEFAULT_ROLLING_CODE_WINDOW 128
#define PROGRAMMING_MODE_TIMEOUT    120000

static bool valid_rolling_code(struct rts_receiver *receiver, uint32_t address,
                               uint16_t code)
{
    // Do we even know this remote?
    if (!rts_remote_store_known_remote(receiver->remote_store, address)) {
        return false;
    }

    // If so, if the rolling code in range?
    uint16_t last_code =
        rts_remote_store_get_code(receiver->remote_store, address);
    if ((code >= last_code) &&
        (code <= (last_code + receiver->rolling_code_window))) {
        // Update last known valid rolling code
        rts_remote_store_set_code(receiver->remote_store, address, code);

        // Reset the rolling code window
        receiver->rolling_code_window = DEFAULT_ROLLING_CODE_WINDOW;

        return true;
    } else {
        // Decrease the rolling code window
        if (receiver->rolling_code_window > 1) {
            receiver->rolling_code_window /= 2;
        }
    }

    return false;
}

static void process_frame(struct rts_frame *frame, uint8_t count,
                          uint32_t duration, void *user_data)
{
    struct rts_receiver *receiver = (struct rts_receiver *)user_data;

    // Determine if this frame is significant enough to fire an event.
    // We care about initial frames, and then certain repeated frames which
    // signify the button has been held down for a while, but we can ignore
    // the rest.
    uint8_t event = RTS_RECEIVER_EVENT_NONE;
    if (count == 0) {
        event = RTS_RECEIVER_EVENT_PRESS;
    } else if (duration >= HOLD_DURATION &&
               receiver->event_fired < RTS_RECEIVER_EVENT_HOLD) {
        event = RTS_RECEIVER_EVENT_HOLD;
    } else if (duration >= HOLD_2_DURATION &&
               receiver->event_fired < RTS_RECEIVER_EVENT_HOLD_2) {
        event = RTS_RECEIVER_EVENT_HOLD_2;
    } else if (duration >= HOLD_3_DURATION &&
               receiver->event_fired < RTS_RECEIVER_EVENT_HOLD_3) {
        event = RTS_RECEIVER_EVENT_HOLD_3;
    } else {
        return;
    }

    switch (receiver->mode) {
    case RTS_RECEIVER_MODE_PROGRAMMING:
        if (event == RTS_RECEIVER_EVENT_PRESS &&
            frame->command == RTS_COMMAND_PROG) {
            // Pair or unpair this remote
            if (rts_remote_store_known_remote(receiver->remote_store,
                                              frame->remote_address)) {
                rts_remote_store_forget(receiver->remote_store,
                                        frame->remote_address);
            } else {
                rts_remote_store_set_code(receiver->remote_store,
                                          frame->remote_address,
                                          frame->rolling_code);
            }

            // Return to command mode
            rts_receiver_set_mode(receiver, RTS_RECEIVER_MODE_COMMAND);
        } else if (event == RTS_RECEIVER_EVENT_HOLD &&
                   frame->command == RTS_COMMAND_MY_UP_DOWN) {
            rts_receiver_set_mode(receiver, RTS_RECEIVER_MODE_OFF);
        } else {
            // TODO: Verbose log?
        }

        break;

    case RTS_RECEIVER_MODE_COMMAND:
        // Check this is a known remote with a valid rolling code
        if (!valid_rolling_code(receiver, frame->remote_address,
                                frame->rolling_code)) {
            return;
        }

        if (event == RTS_RECEIVER_EVENT_HOLD &&
            frame->command == RTS_COMMAND_PROG) {
            // Enter programming mode if the PROG button is held
            rts_receiver_set_mode(receiver, RTS_RECEIVER_MODE_PROGRAMMING);
        } else {
            // Pass all other events on to the user-provided callback
            if (receiver->event_callback) {
                receiver->event_callback(event, frame,
                                         receiver->event_user_data);
            }
        }

        break;

    default:
        break;
    }

    // Save which event we are processing, to prevent repeat events
    receiver->event_fired = event;
}

void rts_receiver_init(struct rts_receiver *receiver,
                       struct rts_pulse_source *pulse_source,
                       struct rts_remote_store *remote_store)
{
    receiver->pulse_source        = pulse_source;
    receiver->remote_store        = remote_store;
    receiver->mode                = RTS_RECEIVER_MODE_OFF;
    receiver->event_fired         = RTS_RECEIVER_EVENT_NONE;
    receiver->rolling_code_window = DEFAULT_ROLLING_CODE_WINDOW;

    rts_frame_builder_init(&receiver->frame_builder, RTS_TIMINGS_DEFAULT);
    rts_frame_builder_set_callback(&receiver->frame_builder, process_frame,
                                   receiver);
    pulse_source->frame_builder = &receiver->frame_builder;
}

void rts_receiver_set_event_callback(struct rts_receiver *receiver,
                                     void (*callback)(uint8_t event,
                                                      struct rts_frame *frame,
                                                      void *user_data),
                                     void *user_data)
{
    receiver->event_callback  = callback;
    receiver->event_user_data = user_data;
}

void rts_receiver_set_mode_callback(struct rts_receiver *receiver,
                                    void (*callback)(uint8_t mode,
                                                     void *user_data),
                                    void *user_data)
{
    receiver->mode_callback  = callback;
    receiver->mode_user_data = user_data;
}

void rts_receiver_set_mode(struct rts_receiver *receiver, uint8_t mode)
{
    // Don't do anything if we are already in this mode
    if (mode == receiver->mode) {
        return;
    }

    // Enable or disable pulses if our mode is set to
    if (mode == RTS_RECEIVER_MODE_OFF) {
        rts_pulse_source_disable(receiver->pulse_source);
    } else if (receiver->mode == RTS_RECEIVER_MODE_OFF) {
        rts_pulse_source_enable(receiver->pulse_source);
    }

    // Save state
    receiver->mode              = mode;
    receiver->mode_last_changed = hal_millis();

    // Fire the user provided callback
    if (receiver->mode_callback) {
        receiver->mode_callback(mode, receiver->mode_user_data);
    }
}

void rts_receiver_forget_all_remotes(struct rts_receiver *receiver)
{
    rts_remote_store_clear(receiver->remote_store);
}

void rts_receiver_update(struct rts_receiver *receiver)
{
    rts_pulse_source_update(receiver->pulse_source);

    // Automatically leave programming mode after 2 minutes
    if (receiver->mode == RTS_RECEIVER_MODE_PROGRAMMING &&
        (hal_millis() - receiver->mode_last_changed) >
            PROGRAMMING_MODE_TIMEOUT) {
        rts_receiver_set_mode(receiver, RTS_RECEIVER_MODE_COMMAND);
    }
}