#include "rts_remote_store_memory.h"

#include <stdlib.h>

struct remote_data {
    uint8_t num_remotes;
    uint32_t *remote_addresses;
    uint16_t *rolling_codes;
};

static int8_t remote_index(struct rts_remote_store *store,
                           uint32_t remote_address)
{
    struct remote_data *data = (struct remote_data *)store->user_data_ptr;

    for (uint8_t i = 0; i < data->num_remotes; i++) {
        if (remote_address == data->remote_addresses[i]) {
            return i;
        }
    }

    return -1;
}

static int8_t get_code(struct rts_remote_store *store, uint32_t remote_address,
                       uint16_t *rolling_code)
{
    struct remote_data *data = (struct remote_data *)store->user_data_ptr;

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    *rolling_code = data->rolling_codes[idx];
    return RTS_ERR_NONE;
}

static int8_t set_code(struct rts_remote_store *store, uint32_t remote_address,
                       uint16_t rolling_code)
{
    struct remote_data *data = (struct remote_data *)store->user_data_ptr;

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        // Add the remote address at the end
        data->remote_addresses[data->num_remotes] = remote_address;
        idx                                       = data->num_remotes;

        // Increment known remote count
        data->num_remotes++;
    }

    data->rolling_codes[idx] = rolling_code;

    return RTS_ERR_NONE;
}

static int8_t forget(struct rts_remote_store *store, uint32_t remote_address)
{
    struct remote_data *data = (struct remote_data *)store->user_data_ptr;

    if (data->num_remotes == 0) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    // Shift all remotes down by 1
    for (int i = idx; i < data->num_remotes - 1; i++) {
        data->remote_addresses[i] = data->remote_addresses[i + 1];
        data->rolling_codes[i]    = data->rolling_codes[i + 1];
    }

    // Decrease known remote count
    data->num_remotes--;

    return RTS_ERR_NONE;
}

static int8_t clear(struct rts_remote_store *store)
{
    struct remote_data *data = (struct remote_data *)store->user_data_ptr;

    data->num_remotes = 0;

    return RTS_ERR_NONE;
}

void rts_remote_store_init_memory(struct rts_remote_store *store,
                                  uint8_t max_remotes)
{
    store->get_code = get_code;
    store->set_code = set_code;
    store->forget   = forget;
    store->clear    = clear;

    struct remote_data *data = malloc(sizeof(struct remote_data));
    data->remote_addresses =
        malloc(sizeof(*data->remote_addresses) * max_remotes);
    data->rolling_codes = malloc(sizeof(*data->rolling_codes) * max_remotes);
    data->num_remotes   = 0;

    // TODO: Check malloc return codes

    store->user_data_ptr = data;
}