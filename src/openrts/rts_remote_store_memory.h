#ifndef RTS_REMOTE_STORE_MEMORY_H
#define RTS_REMOTE_STORE_MEMORY_H

#include "rts_remote_store.h"

#define MAX_REMOTES 16

/**
 * @file
 */

/**
 * @addtogroup openrts
 * @{
 */

// Internal struct to hold remotes/rolling codes
struct rts_remote_store_memory_data {
    int file_handle;
    struct {
        uint8_t num_remotes;
        uint32_t remote_addresses[MAX_REMOTES];
        uint16_t rolling_codes[MAX_REMOTES];
    } * store;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize an rts_remote_store which stores remotes and rolling codes in
 * memory.
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct to initialize
 */
void rts_remote_store_init_memory(struct rts_remote_store *store);

// These functions are shared by rts_remote_store_mmap
int8_t rts_remote_store_get_code_memory(struct rts_remote_store *store,
                                        uint32_t remote_address,
                                        uint16_t *rolling_code);

int8_t rts_remote_store_set_code_memory(struct rts_remote_store *store,
                                        uint32_t remote_address,
                                        uint16_t rolling_code);

int8_t rts_remote_store_forget_memory(struct rts_remote_store *store,
                                      uint32_t remote_address);

int8_t rts_remote_store_clear_memory(struct rts_remote_store *store);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @}
 */

#endif // RTS_REMOTE_STORE_MEMORY_H