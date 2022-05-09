#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum error_t {
    SOMFYSUITE_ERR_NONE             =  0,
    SOMFYSUITE_ERR_REMOTE_NOT_FOUND = -1,
} error_t;

typedef struct rts_remote_store_t {
    error_t (*get_code_fn)(struct rts_remote_store_t *store, uint32_t address, uint16_t *code);
    error_t (*set_code_fn)(struct rts_remote_store_t *store, uint32_t address, uint16_t code);
    error_t (*forget_fn)(struct rts_remote_store_t *store, uint32_t address);
    error_t (*clear_fn)(struct rts_remote_store_t *store);

    union {
        void *user_data_ptr;
        int user_data_int;
    };
} rts_remote_store_t;

void rts_remote_store_set_code(rts_remote_store_t *store, uint32_t remote_address, uint16_t rolling_code);
uint16_t rts_remote_store_get_code(rts_remote_store_t *store, uint32_t remote_address);
uint16_t rts_remote_store_next_code(rts_remote_store_t *store, uint32_t remote_address);
bool rts_remote_store_known_remote(rts_remote_store_t *store, uint32_t remote_address);
void rts_remote_store_forget(rts_remote_store_t *store, uint32_t remote_address);
void rts_remote_store_clear(rts_remote_store_t *store);

#ifdef __cplusplus
} // extern "C"
#endif