#ifndef RTS_REMOTE_STORE_NVS_H
#define RTS_REMOTE_STORE_NVS_H

#include "../rts_remote_store.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize an rts_remote_store which stores remotes and rolling codes in
 * ESP-IDF's NVS (Non-volatile storage) on ESP8266 and ESP32 devices.
 *
 * @note Only available on ESP8266/ESP32 devices
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct to initialize
 */
void rts_remote_store_init_nvs(struct rts_remote_store *store);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_REMOTE_STORE_NVS_H