#include "rts_frame_builder.h"

#include <string.h>

#include "hal/timing.h"
#include "rts_frame.h"

static inline bool _matches_timing(uint32_t time, uint32_t target, uint16_t tolerance) {
    return time > target - tolerance && time < target + tolerance;
}

static void _process_complete_bytes(rts_frame_builder_t *builder, uint8_t *bytes) {
    if(builder->callback == NULL) {
        // SOMFYSUITE_LOG_DEBUG("[Warning] Skipping processing, no callback attached\n");
        return;
    }

    // Unscramble frame
    uint8_t unscrambled[RTS_FRAME_BYTES];
    rts_frame_deobfuscate_bytes(unscrambled, bytes);

    // Validate checksum
    if(rts_frame_generate_checksum(unscrambled) != 0) {
        // SOMFYSUITE_LOG_DEBUG("[Warning] Skipping frame with bad checksum\n");
        return;
    }

    // Check if we've seen this frame before
    // NOTE: This assumes we are listening to a single remote
    uint32_t now = hal_millis();
    if(memcmp(bytes, builder->last_bytes, RTS_FRAME_BYTES) != 0) {
        // New frame
        builder->frame_repeat_count = 0;
        builder->frame_first_seen = now;
        memcpy(builder->last_bytes, bytes, RTS_FRAME_BYTES);
    } else {
        // Repeat frame
        builder->frame_repeat_count++;
    }

    // Construct RTSFrame object from bytes
    rts_frame_t frame;
    rts_frame_from_bytes(&frame, unscrambled);
    // RTSFrame frame(unscrambled);
    uint32_t frame_repeat_duration = now - builder->frame_first_seen;

    // Fire "frame" callback
    builder->callback(&frame, builder->frame_repeat_count, frame_repeat_duration, builder->callback_user_data);
}

void rts_frame_builder_init(rts_frame_builder_t *builder, rts_timings_t *timings) {
    builder->timings = timings;
    builder->timing_tolerance = timings->symbol / 2;

    builder->mode = RTS_FRAME_BUILDER_AWAITING_SYNC;
    builder->preamble_count = 0;

    builder->frame_repeat_count = 0;
    builder->frame_first_seen = 0;
    builder->callback = NULL;
    builder->callback_user_data = NULL;

    memset(builder->last_bytes, 0, RTS_FRAME_BYTES);
}

void rts_frame_builder_handle_pulse(rts_frame_builder_t *builder, bool state, uint32_t micros) {
    switch(builder->mode) {
        case RTS_FRAME_BUILDER_AWAITING_SYNC:
            if(_matches_timing(micros, builder->timings->preamble_high, builder->timing_tolerance) ||
               _matches_timing(micros, builder->timings->preamble_low, builder->timing_tolerance))
            {
                builder->preamble_count++;
            } else if(_matches_timing(micros, builder->timings->sync_high, builder->timing_tolerance) && builder->preamble_count >= 4) {
                // Clear frame state
                builder->bit_count = 0;
                builder->first_data_pulse = true;
                builder->mid_bit = false;
                memset(builder->bytes, 0, RTS_FRAME_BYTES);

                // Enter data receiving mode
                builder->mode = RTS_FRAME_BUILDER_RECEIVING_DATA;
            } else {
                // Unexpected pulse, start again
                builder->preamble_count = 0;
            }
            break;

        case RTS_FRAME_BUILDER_RECEIVING_DATA: {
            bool isDataPulse = _matches_timing(micros, builder->timings->symbol, builder->timing_tolerance);
            bool isWideDataPulse = _matches_timing(micros, builder->timings->symbol*2, builder->timing_tolerance);

            if(isDataPulse || isWideDataPulse) {
                // How many data symbols does this pulse represent
                int symbols = isWideDataPulse ? 2 : 1;
                if(builder->first_data_pulse) {
                    // First pulse contains "low" part of software sync
                    // so we process once less data symbol here
                    symbols--;
                    builder->first_data_pulse = false;
                }

                // Process the data symbols
                for(int i=0; i<symbols; i++) {
                    if(builder->mid_bit) {
                        if(builder->prev_symbol == state) {
                            builder->mode = RTS_FRAME_BUILDER_AWAITING_SYNC;
                            return;
                        }
                    } else {
                        // Write the bit to the frame
                        builder->bytes[builder->bit_count / 8] |= !state << (7 - builder->bit_count % 8);
                        builder->bit_count++;
                    }

                    builder->mid_bit = !builder->mid_bit;
                }

                // Save symbol state to compare manchester encoding
                builder->prev_symbol = state;
            } else {
                // Unexpected pulse, start again
                builder->mode = RTS_FRAME_BUILDER_AWAITING_SYNC;
                builder->preamble_count = 0;
            }

            break;
        }
    }

    // Handle complete frames
    if(builder->mode == RTS_FRAME_BUILDER_RECEIVING_DATA && builder->bit_count == 56) {
        _process_complete_bytes(builder, builder->bytes);
        builder->mode = RTS_FRAME_BUILDER_AWAITING_SYNC;
    }
}

void rts_frame_builder_set_callback(rts_frame_builder_t *builder, rts_frame_callback_t callback, void *user_data) {
    builder->callback = callback;
    builder->callback_user_data = user_data;
}