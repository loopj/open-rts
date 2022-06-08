#include "rts_remote_store.h"

#include <string.h>

void rts_remote_store_set_code(struct rts_remote_store *store,
                               uint32_t remote_address, uint16_t rolling_code)
{
    if (!store->set_code) {
        // TODO: Log an error
        return;
    }

    store->set_code(store, remote_address, rolling_code);
}

uint16_t rts_remote_store_get_code(struct rts_remote_store *store,
                                   uint32_t remote_address)
{
    if (!store->get_code) {
        // TODO: Log an error
        return 0;
    }

    uint16_t rolling_code;
    int8_t status = store->get_code(store, remote_address, &rolling_code);
    if (status != RTS_ERR_NONE) {
        return 0;
    }

    return rolling_code;
}

uint16_t rts_remote_store_next_code(struct rts_remote_store *store,
                                    uint32_t remote_address)
{
    uint16_t rolling_code = rts_remote_store_get_code(store, remote_address);
    rts_remote_store_set_code(store, remote_address, rolling_code + 1);

    return rolling_code;
}

bool rts_remote_store_known_remote(struct rts_remote_store *store,
                                   uint32_t remote_address)
{
    if (!store->get_code) {
        // TODO: Log an error
        return false;
    }

    uint16_t tmp;
    return store->get_code(store, remote_address, &tmp) == RTS_ERR_NONE;
}

void rts_remote_store_forget(struct rts_remote_store *store,
                             uint32_t remote_address)
{
    if (!store->forget) {
        // TODO: Log an error
        return;
    }

    store->forget(store, remote_address);
}

void rts_remote_store_clear(struct rts_remote_store *store)
{
    if (!store->clear) {
        // TODO: Log an error
        return;
    }

    store->clear(store);
}

void rts_remote_store_close(struct rts_remote_store *store)
{
    if (store->close) {
        store->close(store);
    }

    memset(store, 0, sizeof(struct rts_remote_store));
}