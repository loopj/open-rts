#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t hal_millis();
uint64_t hal_micros();

#ifdef __cplusplus
} // extern "C"
#endif