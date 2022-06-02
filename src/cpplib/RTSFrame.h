#pragma once

#include "rts_frame.h"

class RTSFrame : public rts_frame {
  public:
    RTSFrame(uint8_t *bytes) {
        rts_frame_from_bytes(this, bytes);
    }

    RTSFrame(rts_command command, uint16_t rollingCode, uint32_t remoteAddress) {
        rts_frame_init(this, command, rollingCode, remoteAddress);
    }

    void toBytes(uint8_t *dest, bool obfuscate=false) {
        rts_frame_to_bytes(this, dest, obfuscate);
    }

    static void obfuscateBytes(uint8_t *bytes) {
        rts_frame_obfuscate_bytes(bytes);
    }

    static void deobfuscateBytes(uint8_t *dest, uint8_t *src) {
        rts_frame_deobfuscate_bytes(dest, src);
    }

    static uint8_t generateChecksum(uint8_t *bytes) {
        return rts_frame_generate_checksum(bytes);
    }
};