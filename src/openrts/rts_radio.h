#ifndef RTS_RADIO_H
#define RTS_RADIO_H

#include <ookradio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 */

/**
 * @addtogroup openrts
 * @{
 */

/**
 * The transceiver mode to enter
 */
enum rts_radio_mode {
    RTS_RADIO_MODE_STANDBY,  ///< Standby mode
    RTS_RADIO_MODE_RECEIVE,  ///< Receive mode
    RTS_RADIO_MODE_TRANSMIT, ///< Transmit mode
};

enum rts_radio_module {
    RTS_RADIO_MODULE_RFM69,
    RTS_RADIO_MODULE_SX1278,
};

/**
 * Abstraction layer which configures radio modules for RTS.
 */
struct rts_radio {
    enum rts_radio_module type;
    union {
        struct rfm69 rfm69;
        struct sx1278 sx1278;
    };
};

/**
 * Initialize an rts_radio to use an SX1231/RFM69 radio module.
 *
 * @relates rts_radio
 *
 * @param radio the rts_radio struct to initialize
 * @param spi the spi module to communicate with
 */
void rts_radio_init_rfm69(struct rts_radio *radio, struct spi_module *spi);

/**
 * Initialize an rts_radio to use an SX1278/RFM96 radio module.
 *
 * @relates rts_radio
 *
 * @param radio the rts_radio struct to initialize
 * @param spi the spi module to communicate with
 */
void rts_radio_init_sx1278(struct rts_radio *radio, struct spi_module *spi);

/**
 * Set the radio mode for the specified rts_radio module, eg. standby, receive,
 * or transmit.
 *
 * @relates rts_radio
 *
 * @param radio the rts_radio struct to set the mode for
 * @param mode the rts_radio_mode to enter
 */
void rts_radio_set_mode(struct rts_radio *radio, enum rts_radio_mode mode);

/**
 * @}
 */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_RADIO_H