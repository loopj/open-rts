#ifndef RTS_REMOTE_STORE_MEMORY_H
#define RTS_REMOTE_STORE_MEMORY_H

#include "rts_remote_store.h"

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
 * @param max_remotes the max number of remotes we would like to store
 */
void rts_remote_store_init_memory(struct rts_remote_store *store,
                                  uint8_t max_remotes);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_REMOTE_STORE_MEMORY_H