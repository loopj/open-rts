#include "rts_remote_store.h"

void rts_remote_store_set_code(rts_remote_store_t *store, uint32_t remote_address, uint16_t rolling_code) {
    if(!store->set_code_fn) {
        // TODO: Log an error
        return;
    }

    store->set_code_fn(store, remote_address, rolling_code);
}

uint16_t rts_remote_store_get_code(rts_remote_store_t *store, uint32_t remote_address) {
    if(!store->get_code_fn) {
        // TODO: Log an error
        return 0;
    }

    uint16_t rolling_code;
    error_t status = store->get_code_fn(store, remote_address, &rolling_code);
    if(status != SOMFYSUITE_ERR_NONE) {
        return 0;
    }

    return rolling_code;
}

uint16_t rts_remote_store_next_code(rts_remote_store_t *store, uint32_t remote_address) {
    uint16_t rolling_code = rts_remote_store_get_code(store, remote_address);
    rts_remote_store_set_code(store, remote_address, rolling_code + 1);

    return rolling_code;
}

bool rts_remote_store_known_remote(rts_remote_store_t *store, uint32_t remote_address) {
    if(!store->get_code_fn) {
        // TODO: Log an error
        return false;
    }

    uint16_t tmp;
    return store->get_code_fn(store, remote_address, &tmp) == SOMFYSUITE_ERR_NONE;
}

void rts_remote_store_forget(rts_remote_store_t *store, uint32_t remote_address) {
    if(!store->forget_fn) {
        // TODO: Log an error
        return;
    }

    store->forget_fn(store, remote_address);
}

void rts_remote_store_clear(rts_remote_store_t *store) {
    if(!store->clear_fn) {
        // TODO: Log an error
        return;
    }

    store->clear_fn(store);
}