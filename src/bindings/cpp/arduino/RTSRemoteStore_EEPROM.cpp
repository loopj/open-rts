#include "config.h"

#if OPENRTS_INCLUDE_CPP_BINDINGS && OPENRTS_HAS_EEPROM

#include <EEPROM.h>

#include "RTSRemoteStore_EEPROM.h"

static int _get_remote_index(struct rts_remote_store *store,
                             uint32_t remote_address)
{
    uint8_t num_remotes = 0;
    num_remotes         = EEPROM.get(0, num_remotes);

    for (uint8_t i = 0; i < num_remotes; i++) {
        uint32_t current_remote_address = 0;
        current_remote_address = EEPROM.get(1 + 6 * i, current_remote_address);

        if (remote_address == current_remote_address) {
            return i;
        }
    }

    return -1;
}

static int8_t rts_remote_store_get_code_eeprom(struct rts_remote_store *store,
                                               uint32_t remote_address,
                                               uint16_t *rolling_code)
{
    int idx = _get_remote_index(store, remote_address);
    if (idx == -1) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    uint16_t tmp  = 0;
    *rolling_code = EEPROM.get(1 + 6 * idx + 4, tmp);

    return RTS_ERR_NONE;
}

static int8_t rts_remote_store_set_code_eeprom(struct rts_remote_store *store,
                                               uint32_t remote_address,
                                               uint16_t rolling_code)
{
    int idx = _get_remote_index(store, remote_address);

    // Add new remote if doesn't already exist
    if (idx == -1) {
        uint8_t num_remotes = 0;
        num_remotes         = EEPROM.get(0, num_remotes);

        EEPROM.put(0, num_remotes + 1);
        EEPROM.put(1 + 6 * num_remotes, remote_address);
        idx = num_remotes;
    }

    // Set the code
    EEPROM.put(1 + 6 * idx + 4, rolling_code);

#if defined(ESP8266) || defined(ESP32)
    EEPROM.commit();
#endif

    return RTS_ERR_NONE;
}

static int8_t rts_remote_store_forget_eeprom(struct rts_remote_store *store,
                                             uint32_t remote_address)
{
    uint8_t num_remotes = 0;
    num_remotes         = EEPROM.get(0, num_remotes);
    if (num_remotes == 0) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    int idx = _get_remote_index(store, remote_address);
    if (idx == -1) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    // Shift all remotes down by 1
    for (int i = idx; i < num_remotes - 1; i++) {
        uint32_t next_remote_address = 0;
        next_remote_address = EEPROM.get(1 + 6 * (i + 1), next_remote_address);
        EEPROM.put(1 + 6 * i, next_remote_address);

        uint16_t next_rolling_code = 0;
        next_rolling_code = EEPROM.get(1 + 6 * (i + 1) + 4, next_rolling_code);
        EEPROM.put(1 + 6 * i + 4, next_rolling_code);
    }

    // Decrease known remote count
    EEPROM.put(0, num_remotes - 1);

#if defined(ESP8266) || defined(ESP32)
    EEPROM.commit();
#endif

    return RTS_ERR_NONE;
}

static int8_t rts_remote_store_clear_eeprom(struct rts_remote_store *store)
{
    EEPROM.put(0, 0);

#if defined(ESP8266) || defined(ESP32)
    EEPROM.commit();
#endif

    return RTS_ERR_NONE;
}

RTSRemoteStore_EEPROM::RTSRemoteStore_EEPROM(uint8_t maxRemotes,
                                             uint16_t baseAddress)
{
    rts_remote_store::get_code = &rts_remote_store_get_code_eeprom;
    rts_remote_store::set_code = &rts_remote_store_set_code_eeprom;
    rts_remote_store::forget   = &rts_remote_store_forget_eeprom;
    rts_remote_store::clear    = &rts_remote_store_clear_eeprom;

    this->user_data_int = 0;
}

#endif // OPENRTS_HAS_EEPROM