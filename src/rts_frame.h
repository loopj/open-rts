#ifndef RTS_FRAME_H
#define RTS_FRAME_H

#include "rts_command.h"

#include <stdbool.h>
#include <stdint.h>

#define RTS_FRAME_BYTES 7

/**
 * Represents the message "payload" sent by RTS remote controls.
 *
 * It contains the command (eg. UP, DOWN, etc), the identity of the sender
 * remote_address), and information to verify the authenticity of the payload
 * (checksum, rolling_code, encryption_key).
 */
struct rts_frame {
    /**
     * 8-bit encryption key, typically generated automatically.
     * First 4 bits are typically always 0xA, the last 4 bits increment every
     * button press. Receivers don't typically care about this key, but we'll
     * set it to something sensible automatically when you call a constructor.
     */
    uint8_t encryption_key : 8;

    /**
     * The command we are sending, eg "Up", "Down", "My", or combinations of
     * buttons found on remote controls. See rts_command enum.
     */
    enum rts_command command : 4;

    /**
     * The rolling code of this frame.
     * Rolling codes are sequential, unsigned 16-bit integers sent by remotes
     * that provide some level of protection against cloning attacks.
     * Receivers expect that the rolling code for each paired remote is
     * higher than the previously received code (but not too much higher).
     */
    uint16_t rolling_code : 16;

    /**
     * The three-byte remote address sending this frame.
     * This is used by receivers to confirm this is a known, paired remote,
     * and to validate rolling codes.
     */
    uint32_t remote_address : 24;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize an rts_frame with typical payload. We'll generate a sensible
 * encryption_key automatically.
 *
 * @relates rts_frame
 *
 * @param frame the frame to initialize
 * @param command the rts_command
 * @param rolling_code the rolling code
 * @param remote_address the remote address
 */
void rts_frame_init(struct rts_frame *frame, enum rts_command command,
                    uint16_t rolling_code, uint32_t remote_address);

/**
 * Initialize an rts_frame from the raw (deobfuscated) bytes received.
 *
 * @relates rts_frame
 *
 * @param frame the frame to initialize
 * @param bytes the raw frame bytes to construct from
 */
void rts_frame_from_bytes(struct rts_frame *frame, const uint8_t *bytes);

/**
 * Convert an rts_frame to byte representation, and optionally apply XOR
 * obfuscation to make it ready to send.
 *
 * @relates rts_frame
 *
 * @param frame the frame to convert
 * @param bytes the byte array to store the result in
 * @param obfuscate should we also apply obfuscation to the bytes
 */
void rts_frame_to_bytes(struct rts_frame *frame, uint8_t *bytes,
                        bool obfuscate);

/**
 * Apply in-place XOR obfuscation to a raw byte array representation of a frame.
 *
 * @relates rts_frame
 *
 * @param bytes the raw frame bytes to obfuscate
 */
void rts_frame_obfuscate_bytes(uint8_t *bytes);

/**
 * Apply XOR deobfuscation to a raw byte array representation of a frame.
 *
 * @relates rts_frame
 *
 * @param dest the destination byte array for the deobfuscated frame bytes
 * @param src the raw frame bytes to deobfuscate
 */
void rts_frame_deobfuscate_bytes(uint8_t *dest, const uint8_t *src);

/**
 * Generate a checksum for the raw (deobfuscated) bytes of a frame.
 * Checksum for a valid frame is 0.
 *
 * @relates rts_frame
 *
 * @param bytes the raw deobfuscated frame bytes to check
 */
uint8_t rts_frame_generate_checksum(const uint8_t *bytes);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_FRAME_H