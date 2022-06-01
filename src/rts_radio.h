#ifndef RTS_RADIO_H
#define RTS_RADIO_H

#include "radio/rfm69.h"
#include "radio/spi_module.h"
#include "radio/sx1278.h"

enum rts_radio_mode {
    RTS_RADIO_MODE_STANDBY,
    RTS_RADIO_MODE_RECEIVE,
    RTS_RADIO_MODE_TRANSMIT,
};

enum rts_radio_module {
    RTS_RADIO_MODULE_RFM69,
    RTS_RADIO_MODULE_SX1278,
};

struct rts_radio {
    enum rts_radio_module type;
    union {
        struct rfm69 rfm69;
        struct sx1278 sx1278;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

void rts_radio_init_rfm69(struct rts_radio *radio, struct spi_module *spi,
                          bool use_pa_boost);

void rts_radio_init_sx1278(struct rts_radio *radio, struct spi_module *spi,
                           bool use_pa_boost);

void rts_radio_set_mode(struct rts_radio *radio, enum rts_radio_mode mode);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_RADIO_H