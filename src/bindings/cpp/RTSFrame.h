/**
 * @file
 * @addtogroup cpp
 *
 *  @{
 */

#ifndef RTS_FRAME_CPP_H
#define RTS_FRAME_CPP_H

#include "rts_frame.h"

/**
 * Represents the message "payload" sent by RTS remote controls.
 *
 * It contains the command (eg. UP, DOWN, etc), the identity of the sender
 * remote_address), and information to verify the authenticity of the payload
 * (checksum, rolling_code, encryption_key).
 *
 */
class RTSFrame : public rts_frame
{
  public:
    /**
     * Construct an RTSFrame with typical payload. We'll generate a sensible
     * encryption_key automatically.
     *
     * @param command the rts_command
     * @param rollingCode the rolling code
     * @param remoteAddress the remote address
     */
    RTSFrame(rts_command command, uint16_t rollingCode, uint32_t remoteAddress);

    /**
     * Construct an RTSFrame from the raw (deobfuscated) bytes received.
     *
     * @param bytes the raw frame bytes to construct from
     */
    RTSFrame(uint8_t *bytes);

    /**
     * Construct an RTSFrame by copying the contents from an rts_frame
     * struct.
     *
     * @param frame
     */
    RTSFrame(rts_frame *frame);

    /**
     * Convert an RTSFrame to byte representation, and optionally apply XOR
     * obfuscation to make it ready to send.
     *
     * @param bytes the byte array to store the result in
     * @param obfuscate should we also apply obfuscation to the bytes
     */
    void toBytes(uint8_t *bytes, bool obfuscate = false);

    /**
     * Apply in-place XOR obfuscation to a raw byte array representation of a frame.
     *
     * @param bytes the raw frame bytes to obfuscate
     */
    static void obfuscateBytes(uint8_t *bytes);

    /**
     * Apply XOR deobfuscation to a raw byte array representation of a frame.
     *
     * @param dest the destination byte array for the deobfuscated frame bytes
     * @param src the raw frame bytes to deobfuscate
     */
    static void deobfuscateBytes(uint8_t *dest, uint8_t *src);

    /**
     * Generate a checksum for the raw (deobfuscated) bytes of a frame.
     * Checksum for a valid frame is 0.
     *
     * @param bytes the raw deobfuscated frame bytes to check
     */
    static uint8_t generateChecksum(uint8_t *bytes);
};

#endif // RTS_FRAME_CPP_H

/// @}