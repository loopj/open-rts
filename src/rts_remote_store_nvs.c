#include "config.h"

#if HAS_NVS

#include "rts_remote_store_nvs.h"

#include <nvs.h>
#include <nvs_flash.h>

#define NVS_KEY_LENGTH 16

// TODO: Check nvs_* error codes

static char *_address_str(uint32_t address)
{
    static char address_str[NVS_KEY_LENGTH];
    snprintf(address_str, NVS_KEY_LENGTH, "%06X", address);

    return address_str;
}

static int8_t get_code(struct rts_remote_store *store, uint32_t remote_address,
                       uint16_t *rolling_code)
{
    esp_err_t status = nvs_get_u16(store->user_data_int,
                                   _address_str(remote_address), rolling_code);
    if (status == ESP_OK) {
        return RTS_ERR_NONE;
    }

    return RTS_ERR_REMOTE_NOT_FOUND;
}

static int8_t set_code(struct rts_remote_store *store, uint32_t remote_address,
                       uint16_t rolling_code)
{
    nvs_set_u16(store->user_data_int, _address_str(remote_address),
                rolling_code);
    nvs_commit(store->user_data_int);

    return RTS_ERR_NONE;
}

static int8_t forget(struct rts_remote_store *store, uint32_t remote_address)
{
    esp_err_t status =
        nvs_erase_key(store->user_data_int, _address_str(remote_address));
    if (status == ESP_ERR_NVS_NOT_FOUND) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    nvs_commit(store->user_data_int);
    return RTS_ERR_NONE;
}

static int8_t clear(struct rts_remote_store *store)
{
    nvs_erase_all(store->user_data_int);
    nvs_commit(store->user_data_int);

    return RTS_ERR_NONE;
}

static void close(struct rts_remote_store *store)
{
    nvs_close(store->user_data_int);
    nvs_flash_deinit();
}

void rts_remote_store_init_nvs(struct rts_remote_store *store)
{
    store->get_code = get_code;
    store->set_code = set_code;
    store->forget   = forget;
    store->clear    = clear;
    store->close    = close;

    nvs_flash_init();
    nvs_open("openrts", NVS_READWRITE, (nvs_handle *)(&store->user_data_int));
}

#endif /* HAS_NVS */