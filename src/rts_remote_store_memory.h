#include "rts_remote_store.h"

#define RTS_REMOTE_STORE_MEMORY_MAX_REMOTES 16

#ifdef __cplusplus
extern "C" {
#endif

void rts_remote_store_init_memory(rts_remote_store_t *store);
error_t rts_remote_store_get_code_memory(rts_remote_store_t *store, uint32_t remote_address, uint16_t *rolling_code);
error_t rts_remote_store_set_code_memory(rts_remote_store_t *store, uint32_t remote_address, uint16_t rolling_code);
error_t rts_remote_store_forget_memory(rts_remote_store_t *store, uint32_t remote_address);
error_t rts_remote_store_clear_memory(rts_remote_store_t *store);

#ifdef __cplusplus
} // extern "C"
#endif
