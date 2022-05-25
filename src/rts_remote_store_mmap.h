#ifndef RTS_REMOTE_STORE_MEMORY_H
#define RTS_REMOTE_STORE_MEMORY_H

#include "rts_remote_store.h"

#ifdef __cplusplus
extern "C" {
#endif

void rts_remote_store_init_mmap(struct rts_remote_store *store,
                                const char *filename);

void rts_remote_store_free_mmap(struct rts_remote_store *store);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_REMOTE_STORE_MEMORY_H