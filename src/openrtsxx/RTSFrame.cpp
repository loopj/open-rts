#include "openrts/config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS

#include "RTSFrame.hpp"

RTSFrame::RTSFrame(rts_command command, uint16_t rollingCode,
                   uint32_t remoteAddress)
{
    rts_frame_init(this, command, rollingCode, remoteAddress);
}

RTSFrame::RTSFrame(uint8_t *bytes)
{
    rts_frame_from_bytes(this, bytes);
}

RTSFrame::RTSFrame(rts_frame *frame)
{
    this->command        = frame->command;
    this->rolling_code   = frame->rolling_code;
    this->remote_address = frame->remote_address;
    this->encryption_key = frame->encryption_key;
}

void RTSFrame::toBytes(uint8_t *bytes, bool obfuscate)
{
    rts_frame_to_bytes(this, bytes, obfuscate);
}

void RTSFrame::obfuscateBytes(uint8_t *bytes)
{
    rts_frame_obfuscate_bytes(bytes);
}

void RTSFrame::deobfuscateBytes(uint8_t *dest, uint8_t *src)
{
    rts_frame_deobfuscate_bytes(dest, src);
}

uint8_t RTSFrame::generateChecksum(uint8_t *bytes)
{
    return rts_frame_generate_checksum(bytes);
}

#endif // OPENRTS_INCLUDE_CPP_BINDINGS