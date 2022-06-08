/**
 * @file
 * @addtogroup c
 *  @{
 */

#ifndef RTS_REMOTE_STORE_H
#define RTS_REMOTE_STORE_H

#include <stdbool.h>
#include <stdint.h>

// TODO: Centralize error codes
enum {
    RTS_ERR_NONE             = 0,
    RTS_ERR_REMOTE_NOT_FOUND = -1,
};

/**
 * Provides an interface for a datastore which contains details about remote
 * controls and rolling codes.
 *
 * Implementations must define the get_code, set_code, forget, and clear
 * functions and set the function pointers in the rts_remote_store struct.
 */
struct rts_remote_store {
    int8_t (*get_code)(struct rts_remote_store *store, uint32_t remote_address,
                       uint16_t *code);
    int8_t (*set_code)(struct rts_remote_store *store, uint32_t remote_address,
                       uint16_t code);
    int8_t (*forget)(struct rts_remote_store *store, uint32_t remote_address);
    int8_t (*clear)(struct rts_remote_store *store);
    void (*close)(struct rts_remote_store *store);

    union {
        void *user_data_ptr;
        int user_data_int;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the rolling code for this remote, create if doesn't exist
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct to set the code to
 * @param remote_address the address of the remote control
 * @param rolling_code the rolling code to set
 */
void rts_remote_store_set_code(struct rts_remote_store *store,
                               uint32_t remote_address, uint16_t rolling_code);

/**
 * Get the rolling code for this remote
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct to get the code from
 * @param remote_address the address of the remote control
 *
 * @return the rolling code for this remote
 */
uint16_t rts_remote_store_get_code(struct rts_remote_store *store,
                                   uint32_t remote_address);

/**
 * Get the rolling code for this remote, then increment and persist
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct to get the code from
 * @param remote_address the address of the remote control
 *
 * @return the rolling code for this remote
 */
uint16_t rts_remote_store_next_code(struct rts_remote_store *store,
                                    uint32_t remote_address);

/**
 * Check if this is a known remote address
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct to check in
 * @param remote_address the address of the remote control
 */
bool rts_remote_store_known_remote(struct rts_remote_store *store,
                                   uint32_t remote_address);

/**
 * Forget a specific remote
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct
 * @param remote_address the address of the remote control to forget
 */
void rts_remote_store_forget(struct rts_remote_store *store,
                             uint32_t remote_address);

/**
 * Clear all remotes and rolling codes
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store struct to clear
 */
void rts_remote_store_clear(struct rts_remote_store *store);

/**
 * Close and free any resources allocated via a previous call to
 * rts_remote_store_init*()
 *
 * @relates rts_remote_store
 *
 * @param store the rts_remote_store to close
 */
void rts_remote_store_close(struct rts_remote_store *store);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_REMOTE_STORE_H

/// @}