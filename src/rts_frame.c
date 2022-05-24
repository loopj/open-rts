#include "rts_frame.h"

void rts_frame_init(struct rts_frame *frame, enum rts_command command,
                    uint16_t rolling_code, uint32_t address)
{
    frame->command        = command;
    frame->remote_address = address;
    frame->rolling_code   = rolling_code;

    // Generate an encryption key that looks like one from a remote
    // All my remotes have the first nibble as 0xA, and the second
    // nibble as a number that increments for every button press.
    // Receivers don't seem to care about this.
    frame->encryption_key = (rolling_code & 0xF) | 0xA0;
}

void rts_frame_from_bytes(struct rts_frame *frame, const uint8_t *bytes)
{
    // Unpack the encryption key
    frame->encryption_key = bytes[0];

    // Unpack command. The other half of this byte is the checksum.
    frame->command = bytes[1] >> 4;

    // Unpack rolling code
    frame->rolling_code = bytes[2] << 8 | bytes[3];

    // Unpack remote address.
    // This byte order makes the most sense based on observing real remotes
    // which have multiple channels. When changing the channel on a remote,
    // the last byte increases as the channel increases.
    frame->remote_address =
        bytes[4] | (uint32_t)bytes[5] << 8 | (uint32_t)bytes[6] << 16;
}

void rts_frame_to_bytes(struct rts_frame *frame, uint8_t *bytes, bool obfuscate)
{
    // Pack frame into bytes
    bytes[0] = frame->encryption_key;
    bytes[1] = frame->command << 4;
    bytes[2] = frame->rolling_code >> 8;
    bytes[3] = frame->rolling_code;
    bytes[4] = frame->remote_address;
    bytes[5] = frame->remote_address >> 8;
    bytes[6] = frame->remote_address >> 16;

    // Generate the checksum
    bytes[1] |= rts_frame_generate_checksum(bytes);

    // Obfuscate if required
    if (obfuscate) {
        rts_frame_obfuscate_bytes(bytes);
    }
}

void rts_frame_obfuscate_bytes(uint8_t *bytes)
{
    // XOR between the byte to obfuscate and the previous obfuscated byte
    for (uint8_t i = 1; i < RTS_FRAME_BYTES; i++) {
        bytes[i] = bytes[i] ^ bytes[i - 1];
    }
}

void rts_frame_deobfuscate_bytes(uint8_t *dest, const uint8_t *src)
{
    // Reverse the above obfuscation
    dest[0] = src[0];
    for (uint8_t i = 1; i < RTS_FRAME_BYTES; i++) {
        dest[i] = src[i] ^ src[i - 1];
    }
}

uint8_t rts_frame_generate_checksum(const uint8_t *bytes)
{
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < RTS_FRAME_BYTES; i++) {
        checksum = checksum ^ bytes[i] ^ (bytes[i] >> 4);
    }

    return checksum & 0xF;
}