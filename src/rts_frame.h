#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "rts_command.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTS_FRAME_BYTES 7

typedef struct rts_frame_t {
    uint8_t encryption_key;
    rts_command_t command : 4;
    uint16_t rolling_code;
    uint32_t remote_address : 24;
} rts_frame_t;

void rts_frame_init(rts_frame_t *frame, uint8_t command, uint16_t rolling_code, uint32_t remoteAddress);
void rts_frame_from_bytes(rts_frame_t *frame, uint8_t *bytes);
void rts_frame_to_bytes(rts_frame_t *frame, uint8_t *bytes, bool obfuscate);
void rts_frame_obfuscate_bytes(uint8_t *bytes);
void rts_frame_deobfuscate_bytes(uint8_t *dest, uint8_t *src);
uint8_t rts_frame_generate_checksum(uint8_t *bytes);

#ifdef __cplusplus
} // extern "C"
#endif