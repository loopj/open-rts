#ifndef RTS_FRAME_CPP_H
#define RTS_FRAME_CPP_H

#include "rts_frame.h"

class RTSFrame : public rts_frame
{
  public:
    RTSFrame(uint8_t *bytes);
    RTSFrame(rts_command command, uint16_t rollingCode, uint32_t remoteAddress);
    RTSFrame(rts_frame *frame);

    void toBytes(uint8_t *dest, bool obfuscate = false);

    static void obfuscateBytes(uint8_t *bytes);
    static void deobfuscateBytes(uint8_t *dest, uint8_t *src);
    static uint8_t generateChecksum(uint8_t *bytes);
};

#endif // RTS_FRAME_CPP_H