#ifndef RTS_REMOTE_STORE_MMAP_H
#define RTS_REMOTE_STORE_MMAP_H

#include "../rts_remote_store.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 */

/**
 * @addtogroup openrts
 * @{
 */

/**
 * Initialize an rts_remote_store which stores remotes and rolling codes in
 * a memory-mapped file on POSIX systems.
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct to initialize
 * @param filename the path of the filename to store remote data
 */
void rts_remote_store_init_mmap(struct rts_remote_store *store,
                                const char *filename);

/**
 * @}
 */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_REMOTE_STORE_MEMORY_H