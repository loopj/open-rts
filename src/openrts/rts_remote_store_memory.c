#include <stdlib.h>

#include "config.h"

#include "rts_remote_store_memory.h"

static int8_t remote_index(struct rts_remote_store *store,
                           uint32_t remote_address)
{
    struct rts_remote_store_memory_data *user_data = store->user_data_ptr;

    for (uint8_t i = 0; i < user_data->store->num_remotes; i++) {
        if (remote_address == user_data->store->remote_addresses[i]) {
            return i;
        }
    }

    return -1;
}

int8_t rts_remote_store_get_code_memory(struct rts_remote_store *store,
                                        uint32_t remote_address,
                                        uint16_t *rolling_code)
{
    struct rts_remote_store_memory_data *user_data = store->user_data_ptr;

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    *rolling_code = user_data->store->rolling_codes[idx];
    return RTS_ERR_NONE;
}

int8_t rts_remote_store_set_code_memory(struct rts_remote_store *store,
                                        uint32_t remote_address,
                                        uint16_t rolling_code)
{
    struct rts_remote_store_memory_data *user_data = store->user_data_ptr;

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        // Add the remote address at the end
        uint8_t num_remotes = user_data->store->num_remotes;
        user_data->store->remote_addresses[num_remotes] = remote_address;
        idx                                             = num_remotes;

        // Increment known remote count
        user_data->store->num_remotes++;
    }

    user_data->store->rolling_codes[idx] = rolling_code;

    return RTS_ERR_NONE;
}

int8_t rts_remote_store_forget_memory(struct rts_remote_store *store,
                                      uint32_t remote_address)
{
    struct rts_remote_store_memory_data *user_data = store->user_data_ptr;

    if (user_data->store->num_remotes == 0) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    // Shift all remotes down by 1
    for (int i = idx; i < user_data->store->num_remotes - 1; i++) {
        user_data->store->remote_addresses[i] =
            user_data->store->remote_addresses[i + 1];
        user_data->store->rolling_codes[i] =
            user_data->store->rolling_codes[i + 1];
    }

    // Decrease known remote count
    user_data->store->num_remotes--;

    return RTS_ERR_NONE;
}

int8_t rts_remote_store_clear_memory(struct rts_remote_store *store)
{
    struct rts_remote_store_memory_data *user_data = store->user_data_ptr;

    user_data->store->num_remotes = 0;

    return RTS_ERR_NONE;
}

static void rts_remote_store_close_memory(struct rts_remote_store *store)
{
    struct rts_remote_store_memory_data *user_data = store->user_data_ptr;
    free(user_data->store);
    free(user_data);
}

void rts_remote_store_init_memory(struct rts_remote_store *store)
{
    struct rts_remote_store_memory_data *user_data = malloc(sizeof(user_data));
    user_data->store              = malloc(sizeof(user_data->store));
    user_data->store->num_remotes = 0;

    store->get_code      = rts_remote_store_get_code_memory;
    store->set_code      = rts_remote_store_set_code_memory;
    store->forget        = rts_remote_store_forget_memory;
    store->clear         = rts_remote_store_clear_memory;
    store->close         = rts_remote_store_close_memory;
    store->user_data_ptr = user_data;
}