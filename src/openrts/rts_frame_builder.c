#include <string.h>

#include "hal.h"
#include "rts_frame_builder.h"

enum {
    AWAITING_SYNC = 0,
    RECEIVING_DATA,
};

static void process_bytes(struct rts_frame_builder *builder, uint8_t *bytes)
{
    if (builder->callback == NULL) {
        // TODO: Log a warning
        return;
    }

    // Unscramble frame
    uint8_t unscrambled[RTS_FRAME_BYTES];
    rts_frame_deobfuscate_bytes(unscrambled, bytes);

    // Validate checksum
    if (rts_frame_generate_checksum(unscrambled) != 0) {
        // TODO: Log a warning
        return;
    }

    // Check if we've seen this frame before
    // NOTE: This assumes we are listening to a single remote
    uint32_t now = hal_millis();
    if (memcmp(bytes, builder->last_bytes, RTS_FRAME_BYTES) != 0) {
        // New frame
        builder->frame_repeat_count = 0;
        builder->frame_first_seen   = now;
        memcpy(builder->last_bytes, bytes, RTS_FRAME_BYTES);
    } else {
        // Repeat frame
        builder->frame_repeat_count++;
    }

    // Construct RTSFrame object from bytes
    struct rts_frame frame;
    rts_frame_from_bytes(&frame, unscrambled);

    // Fire "frame" callback
    builder->callback(&frame, builder->frame_repeat_count,
                      now - builder->frame_first_seen,
                      builder->callback_user_data);
}

static bool matches_timing(uint32_t time, uint32_t target, uint16_t tolerance)
{
    return time > target - tolerance && time < target + tolerance;
}

static bool is_preamble_pulse(struct rts_frame_builder *b, uint32_t time)
{
    return matches_timing(time, b->timings->preamble_high, b->tolerance) ||
           matches_timing(time, b->timings->preamble_low, b->tolerance);
}

static bool is_sync_pulse(struct rts_frame_builder *b, uint32_t time)
{
    return matches_timing(time, b->timings->sync_high, b->tolerance);
}

static bool is_data_pulse(struct rts_frame_builder *b, uint32_t time,
                          uint8_t *symbols)
{
    if (matches_timing(time, b->timings->symbol, b->tolerance)) {
        *symbols = 1;
        return true;
    } else if (matches_timing(time, b->timings->symbol * 2, b->tolerance)) {
        *symbols = 2;
        return true;
    }

    return false;
}

void rts_frame_builder_init(struct rts_frame_builder *builder,
                            struct rts_timings *timings)
{
    memset(builder, 0, sizeof(struct rts_frame_builder));

    builder->timings   = timings;
    builder->tolerance = timings->symbol / 2;
}

void rts_frame_builder_handle_pulse(struct rts_frame_builder *builder,
                                    bool state, uint32_t micros)
{
    uint8_t symbols;

    switch (builder->mode) {
    case AWAITING_SYNC:
        if (is_preamble_pulse(builder, micros)) {
            builder->preambles++;
        } else if (is_sync_pulse(builder, micros) && builder->preambles >= 4) {
            // Clear frame state
            builder->bits             = 0;
            builder->first_data_pulse = true;
            builder->mid_bit          = false;
            memset(builder->bytes, 0, RTS_FRAME_BYTES);

            // Enter data receiving mode
            builder->mode = RECEIVING_DATA;
        } else {
            // Unexpected pulse, start again
            builder->preambles = 0;
        }
        break;

    case RECEIVING_DATA:
        if (is_data_pulse(builder, micros, &symbols)) {
            if (builder->first_data_pulse) {
                // First pulse contains "low" part of software sync
                // so we process once less data symbol here
                symbols--;
                builder->first_data_pulse = false;
            }

            // Process the data symbols
            for (int i = 0; i < symbols; i++) {
                if (builder->mid_bit) {
                    if (builder->prev_symbol == state) {
                        builder->mode = AWAITING_SYNC;
                        return;
                    }
                } else {
                    // Write the bit to the frame
                    uint8_t b = builder->bits / 8;
                    builder->bytes[b] |= !state << (7 - builder->bits % 8);
                    builder->bits++;
                }

                builder->mid_bit = !builder->mid_bit;
            }

            // Save symbol state to compare manchester encoding
            builder->prev_symbol = state;
        } else {
            // Unexpected pulse, start again
            builder->mode      = AWAITING_SYNC;
            builder->preambles = 0;
        }

        break;
    }

    // Handle complete frames
    if (builder->mode == RECEIVING_DATA && builder->bits == 56) {
        process_bytes(builder, builder->bytes);
        builder->mode = AWAITING_SYNC;
    }
}

void rts_frame_builder_set_callback(struct rts_frame_builder *builder,
                                    void (*callback)(struct rts_frame *frame,
                                                     uint8_t count,
                                                     uint32_t duration,
                                                     void *user_data),
                                    void *user_data)
{
    builder->callback           = callback;
    builder->callback_user_data = user_data;
}