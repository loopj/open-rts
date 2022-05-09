#include "rts_remote.h"

#include <stddef.h>

#include "rts_pulse_output.h"

void rts_remote_send_command(rts_remote_t *remote, uint32_t address, rts_command_t command, bool repeated) {
    if(remote->remote_store == NULL) {
        return;
    }

    uint16_t rolling_code = repeated ?
        rts_remote_store_get_code(remote->remote_store, address) - 1 :
        rts_remote_store_next_code(remote->remote_store, address);

    rts_frame_t frame;
    rts_frame_init(&frame, command, rolling_code, address);

    rts_remote_send_frame(remote, &frame, repeated);
}

void rts_remote_send_frame(rts_remote_t *remote, rts_frame_t *frame, bool repeated) {
    if(!remote || !remote->pulse_output || !frame) {
        return;
    }

    // Encode the frame for sending
    uint8_t bytes[RTS_FRAME_BYTES];
    rts_frame_to_bytes(frame, bytes, true);

    // Enable the pulse output
    rts_pulse_output_enable(remote->pulse_output);

    if(!repeated) {
        // Send the wakeup pulses
        rts_remote_send_pulse(remote, 1, remote->timings->wakeup_high);
        rts_remote_send_pulse(remote, 0, remote->timings->wakeup_low);
    }

    // Decide how many preamble pulses to send
    uint8_t preambleCount = repeated ?
        RTS_REMOTE_REPEAT_PREAMBLE_COUNT :
        RTS_REMOTE_INITIAL_PREAMBLE_COUNT;

    // Send the preamble pulses
    for(uint8_t i=0; i<preambleCount; i++) {
        rts_remote_send_pulse(remote, 1, remote->timings->preamble_high);
        rts_remote_send_pulse(remote, 0, remote->timings->preamble_low);
    }

    // Send software sync pulses
    rts_remote_send_pulse(remote, 1, remote->timings->sync_high);
    rts_remote_send_pulse(remote, 0, remote->timings->sync_low);

    // Send the data
    for(int i=0; i<RTS_FRAME_BYTES; i++) {
        // MSB first
        for(int j = 7; j >= 0; j--) {
            // Grab the bit to send
            bool bit = bytes[i] & (1 << j);

            // Send the bit using manchester encoded pulses
            if(bit == 1) {
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

void rts_remote_send_pulse(rts_remote_t *remote, bool state, uint32_t micros) {
    rts_pulse_output_send_pulse(remote->pulse_output, state, micros);
}