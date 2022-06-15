#include "rts_remote.h"

#include "rts_pulse_output.h"

#include <stddef.h>

#define INITIAL_PREAMBLE_COUNT 2
#define REPEAT_PREAMBLE_COUNT  7

void rts_remote_init(struct rts_remote *remote,
                     struct rts_pulse_output *pulse_output,
                     struct rts_remote_store *remote_store,
                     struct rts_timings *timings)
{
    remote->pulse_output = pulse_output;
    remote->remote_store = remote_store;
    remote->timings      = timings;
}

void rts_remote_send_command(struct rts_remote *remote, uint32_t address,
                             enum rts_command command, bool repeated)
{
    if (remote->remote_store == NULL) {
        return;
    }

    uint16_t rolling_code =
        repeated ? rts_remote_store_get_code(remote->remote_store, address) - 1
                 : rts_remote_store_next_code(remote->remote_store, address);

    struct rts_frame frame;
    rts_frame_init(&frame, command, rolling_code, address);

    rts_remote_send_frame(remote, &frame, repeated);
}

void rts_remote_send_frame(struct rts_remote *remote, struct rts_frame *frame,
                           bool repeated)
{
    if (!remote || !remote->pulse_output || !frame) {
        return;
    }

    // Encode the frame for sending
    uint8_t bytes[RTS_FRAME_BYTES];
    rts_frame_to_bytes(frame, bytes, true);

    // Enable the pulse output
    rts_pulse_output_enable(remote->pulse_output);

    if (!repeated) {
        // Send the wakeup pulses
        rts_remote_send_pulse(remote, 1, remote->timings->wakeup_high);
        rts_remote_send_pulse(remote, 0, remote->timings->wakeup_low);
    }

    // Decide how many preamble pulses to send
    uint8_t preambleCount =
        repeated ? REPEAT_PREAMBLE_COUNT : INITIAL_PREAMBLE_COUNT;

    // Send the preamble pulses
    for (uint8_t i = 0; i < preambleCount; i++) {
        rts_remote_send_pulse(remote, 1, remote->timings->preamble_high);
        rts_remote_send_pulse(remote, 0, remote->timings->preamble_low);
    }

    // Send software sync pulses
    rts_remote_send_pulse(remote, 1, remote->timings->sync_high);
    rts_remote_send_pulse(remote, 0, remote->timings->sync_low);

    // Send the data
    for (int i = 0; i < RTS_FRAME_BYTES; i++) {
        // MSB first
        for (int j = 7; j >= 0; j--) {
            // Grab the bit to send
            bool bit = bytes[i] & (1 << j);

            // Send the bit using manchester encoded pulses
            if (bit == 1) {
                rts_remote_send_pulse(remote, 0, remote->timings->symbol);
                rts_remote_send_pulse(remote, 1, remote->timings->symbol);
            } else {
                rts_remote_send_pulse(remote, 1, remote->timings->symbol);
                rts_remote_send_pulse(remote, 0, remote->timings->symbol);
            }
        }
    }

    // Send the inter-frame sleep pulse
    rts_remote_send_pulse(remote, 0, remote->timings->frame_sleep);

    // Disable the pulse output
    rts_pulse_output_disable(remote->pulse_output);
}

void rts_remote_send_pulse(struct rts_remote *remote, bool state,
                           uint32_t micros)
{
    rts_pulse_output_send_pulse(remote->pulse_output, state, micros);
}