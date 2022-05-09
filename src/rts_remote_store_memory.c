#include <stdlib.h>

#include "rts_remote_store_memory.h"

typedef struct _remote_data_t {
    uint8_t num_remotes;
    uint32_t remote_addresses[RTS_REMOTE_STORE_MEMORY_MAX_REMOTES];
    uint16_t rolling_codes[RTS_REMOTE_STORE_MEMORY_MAX_REMOTES];
} _remote_data_t;

static int8_t _remote_index(rts_remote_store_t *store, uint32_t remote_address) {
    _remote_data_t *data = (_remote_data_t *)store->user_data_ptr;

    for(uint8_t i=0; i<data->num_remotes; i++) {
        if(remote_address == data->remote_addresses[i]) {
            return i;
        }
    }

    return -1;
}

void rts_remote_store_init_memory(rts_remote_store_t *store) {
    store->get_code_fn = &rts_remote_store_get_code_memory;
    store->set_code_fn = &rts_remote_store_set_code_memory;
    store->forget_fn = &rts_remote_store_forget_memory;
    store->clear_fn = &rts_remote_store_clear_memory;

    store->user_data_ptr = malloc(sizeof(_remote_data_t));

    _remote_data_t *data = (_remote_data_t *)store->user_data_ptr;
    data->num_remotes = 0;
}

error_t rts_remote_store_get_code_memory(rts_remote_store_t *store, uint32_t remote_address, uint16_t *rolling_code) {
    _remote_data_t *data = (_remote_data_t *)store->user_data_ptr;

    int idx = _remote_index(store, remote_address);
    if(idx == -1) {
        return SOMFYSUITE_ERR_REMOTE_NOT_FOUND;
    }

    *rolling_code = data->rolling_codes[idx];
    return SOMFYSUITE_ERR_NONE;
}

error_t rts_remote_store_set_code_memory(rts_remote_store_t *store, uint32_t remote_address, uint16_t rolling_code) {
    _remote_data_t *data = (_remote_data_t *)store->user_data_ptr;

    int idx = _remote_index(store, remote_address);
    if(idx == -1) {
        // Add the remote address at the end
        data->remote_addresses[data->num_remotes] = remote_address;
        idx = data->num_remotes;

        // Increment known remote count
        data->num_remotes++;
    }

    data->rolling_codes[idx] = rolling_code;

    return SOMFYSUITE_ERR_NONE;
}

error_t rts_remote_store_forget_memory(rts_remote_store_t *store, uint32_t remote_address) {
    _remote_data_t *data = (_remote_data_t *)store->user_data_ptr;

    if(data->num_remotes == 0) {
        return SOMFYSUITE_ERR_REMOTE_NOT_FOUND;
    }

    int idx = _remote_index(store, remote_address);
    if(idx == -1) {
        return SOMFYSUITE_ERR_REMOTE_NOT_FOUND;
    }

    // Shift all remotes down by 1
    for(int i=idx; i<data->num_remotes - 1; i++) {
        data->remote_addresses[i] = data->remote_addresses[i+1];
        data->rolling_codes[i] = data->rolling_codes[i+1];
    }

    // Decrease known remote count
    data->num_remotes--;

    return SOMFYSUITE_ERR_NONE;
}

error_t rts_remote_store_clear_memory(rts_remote_store_t *store) {
    _remote_data_t *data = (_remote_data_t *)store->user_data_ptr;

    data->num_remotes = 0;

    return SOMFYSUITE_ERR_NONE;
}