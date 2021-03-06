#ifndef RTS_FRAME_HPP
#define RTS_FRAME_HPP

#include <openrts/rts_frame.h>

/**
 * @file
 */

/**
 * @addtogroup openrtsxx
 * @{
 */

/**
 * @brief Represents the message "payload" sent by RTS remote controls.
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
     * @brief Construct an RTSFrame with typical payload, and auto-generated
     *        encryption_key.
     *
     * @param command the rts_command
     * @param rollingCode the rolling code
     * @param remoteAddress the remote address
     */
    RTSFrame(rts_command command, uint16_t rollingCode, uint32_t remoteAddress);

    /**
     * @brief Construct an RTSFrame from the raw (deobfuscated) bytes received.
     *
     * @param bytes the raw frame bytes to construct from
     */
    RTSFrame(uint8_t *bytes);

    /**
     * @brief Construct an RTSFrame by copying the contents of an rts_frame.
     *
     * @param frame
     */
    RTSFrame(rts_frame *frame);

    /**
     * @brief Convert an RTSFrame to byte representation.
     *
     * @param bytes the byte array to store the result in
     * @param obfuscate should we also apply obfuscation to the bytes
     */
    void toBytes(uint8_t *bytes, bool obfuscate = false);

    /**
     * @brief Apply in-place XOR obfuscation to a raw byte representation
     *        of a frame.
     *
     * @param bytes the raw frame bytes to obfuscate
     */
    static void obfuscateBytes(uint8_t *bytes);

    /**
     * @brief Apply XOR deobfuscation to a raw byte representation of a frame.
     *
     * @param dest the destination byte array for the deobfuscated frame bytes
     * @param src the raw frame bytes to deobfuscate
     */
    static void deobfuscateBytes(uint8_t *dest, uint8_t *src);

    /**
     * @brief Generate a checksum for the raw (deobfuscated) bytes of a frame.
     *
     * @param bytes the raw deobfuscated frame bytes to check
     *
     * The checksum for a valid frame should be 0.
     */
    static uint8_t generateChecksum(uint8_t *bytes);
};

/**
 * @}
 */

#endif // RTS_FRAME_HPP