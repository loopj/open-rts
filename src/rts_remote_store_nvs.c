#if defined(ESP_PLATFORM)

#include "rts_remote_store_nvs.h"

#include <nvs.h>
#include <nvs_flash.h>

#define NVS_KEY_LENGTH 16

void rts_remote_store_init_nvs(rts_remote_store_t *store) {
    store->get_code_fn = &rts_remote_store_get_code_nvs;
    store->set_code_fn = &rts_remote_store_set_code_nvs;
    store->forget_fn = &rts_remote_store_forget_nvs;
    store->clear_fn = &rts_remote_store_clear_nvs;

    nvs_flash_init();
    nvs_open("openrts", NVS_READWRITE, (nvs_handle *)(&store->user_data_int));
}

error_t rts_remote_store_get_code_nvs(rts_remote_store_t *store, uint32_t remote_address, uint16_t *rolling_code) {
    char address_string[NVS_KEY_LENGTH];
    snprintf(address_string, NVS_KEY_LENGTH, "%06X", remote_address);

    esp_err_t status = nvs_get_u16(store->user_data_int, address_string, rolling_code);
    if(status == ESP_OK) {
        return SOMFYSUITE_ERR_NONE;
    }

    return SOMFYSUITE_ERR_REMOTE_NOT_FOUND;
}

error_t rts_remote_store_set_code_nvs(rts_remote_store_t *store, uint32_t remote_address, uint16_t rolling_code) {
    char address_string[NVS_KEY_LENGTH];
    snprintf(address_string, NVS_KEY_LENGTH, "%06X", remote_address);

    nvs_set_u16(store->user_data_int, address_string, rolling_code);
    nvs_commit(store->user_data_int);

    return SOMFYSUITE_ERR_NONE;
}

error_t rts_remote_store_forget_nvs(rts_remote_store_t *store, uint32_t remote_address) {
    char address_string[NVS_KEY_LENGTH];
    snprintf(address_string, NVS_KEY_LENGTH, "%06X", remote_address);

    esp_err_t status = nvs_erase_key(store->user_data_int, address_string);
    if(status == ESP_ERR_NVS_NOT_FOUND) {
        return SOMFYSUITE_ERR_REMOTE_NOT_FOUND;
    }

    nvs_commit(store->user_data_int);
    return SOMFYSUITE_ERR_NONE;
}

error_t rts_remote_store_clear_nvs(rts_remote_store_t *store) {
    nvs_erase_all(store->user_data_int);
    nvs_commit(store->user_data_int);

    return SOMFYSUITE_ERR_NONE;
}

#endif