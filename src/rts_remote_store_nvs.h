#include "rts_remote_store.h"

#ifdef __cplusplus
extern "C" {
#endif

void rts_remote_store_init_nvs(rts_remote_store_t *store);
error_t rts_remote_store_get_code_nvs(rts_remote_store_t *store, uint32_t remote_address, uint16_t *rolling_code);
error_t rts_remote_store_set_code_nvs(rts_remote_store_t *store, uint32_t remote_address, uint16_t rolling_code);
error_t rts_remote_store_forget_nvs(rts_remote_store_t *store, uint32_t remote_address);
error_t rts_remote_store_clear_nvs(rts_remote_store_t *store);

#ifdef __cplusplus
} // extern "C"
#endif
