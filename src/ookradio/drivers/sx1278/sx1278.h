#ifndef SX1278_H
#define SX1278_H

#include <stdbool.h>

#include "../../hal/spi_module.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 */

/**
 * @addtogroup ookradio
 * @{
 */

/**
 * An SPI-attached SX1278 or RFM96 radio module
 */
struct sx1278 {
    struct spi_module *spi_module;
    int power;
    int mode;
};

// Oscillator
#define SX1278_FXOSC 32000000.0
#define SX1278_FSTEP (SX1278_FXOSC / 524288)

// Register map
enum {
    SX1278_REG_OP_MODE         = 0x01,
    SX1278_REG_BITRATE_MSB     = 0x02,
    SX1278_REG_BITRATE_LSB     = 0x03,
    SX1278_REG_FRF_MSB         = 0x06,
    SX1278_REG_FRF_MID         = 0x07,
    SX1278_REG_FRF_LSB         = 0x08,
    SX1278_REG_PA_CONFIG       = 0x09,
    SX1278_REG_PA_RAMP         = 0x0A,
    SX1278_REG_OCP             = 0x0B,
    SX1278_REG_RX_BW           = 0x12,
    SX1278_REG_OOK_PEAK        = 0x14,
    SX1278_REG_OOK_FIX         = 0x15,
    SX1278_REG_PACKET_CONFIG_2 = 0x31,
    SX1278_REG_IRQ_FLAGS_1     = 0x3E,
    SX1278_REG_DIO_MAPPING_1   = 0x40,
    SX1278_REG_VERSION         = 0x42,
    SX1278_REG_PA_DAC          = 0x4D,
};

// RegOpMode (0x01)
enum {
    SX1278_LONG_RANGE_MODE        = 0x80,
    SX1278_LONG_RANGE_MODE_OFF    = 0x00,
    SX1278_LONG_RANGE_MODE_ON     = 0x80,
    SX1278_MODULATION_TYPE        = 0x60,
    SX1278_MODULATION_TYPE_FSK    = 0x00,
    SX1278_MODULATION_TYPE_OOK    = 0x20,
    SX1278_LOW_FREQUENCY_MODE     = 0x08,
    SX1278_LOW_FREQUENCY_MODE_OFF = 0x00,
    SX1278_LOW_FREQUENCY_MODE_ON  = 0x08,
    SX1278_MODE                   = 0x07,
    SX1278_MODE_SLEEP             = 0x00,
    SX1278_MODE_STDBY             = 0x01,
    SX1278_MODE_FSTX              = 0x02,
    SX1278_MODE_TX                = 0x03,
    SX1278_MODE_FSRX              = 0x04,
    SX1278_MODE_RX                = 0x05,
};

// RegPaConfig (0x09)
enum {
    SX1278_PA_SELECT          = 0x80,
    SX1278_PA_SELECT_RFO      = 0x00,
    SX1278_PA_SELECT_PA_BOOST = 0x80,
    SX1278_MAX_POWER          = 0x70,
    SX1278_MAX_POWER_MAX      = 0x70,
    SX1278_MAX_POWER_LOW      = 0x20,
    SX1278_OUTPUT_POWER       = 0x0F,
};

// RegRxBw (0x12)
enum {
    SX1278_RX_BW_MANT    = 0x18,
    SX1278_RX_BW_MANT_16 = 0x00,
    SX1278_RX_BW_MANT_20 = 0x08,
    SX1278_RX_BW_MANT_24 = 0x10,
    SX1278_RX_BW_EXP     = 0x07,
};

// RegOokPeak (0x14)
enum {
    SX1278_BIT_SYNC                = 0x20,
    SX1278_BIT_SYNC_ON             = 0x20,
    SX1278_BIT_SYNC_OFF            = 0x00,
    SX1278_OOK_THRESH_TYPE         = 0x18,
    SX1278_OOK_THRESH_TYPE_FIXED   = 0x00,
    SX1278_OOK_THRESH_TYPE_PEAK    = 0x08,
    SX1278_OOK_THRESH_TYPE_AVERAGE = 0x10,
};

// RegPacketConfig2 (0x31)
enum {
    SX1278_DATA_MODE            = 0x40,
    SX1278_DATA_MODE_CONTINUOUS = 0x00,
    SX1278_DATA_MODE_PACKET     = 0x40,
};

// RegIrqFlags1 (0x3E)
enum {
    SX1278_MODE_READY = 0x80,
};

// RegPaDac (0x4D)
enum {
    SX1278_PA_DAC          = 0x07,
    SX1278_PA_DAC_ENABLED  = 0x07,
    SX1278_PA_DAC_DISABLED = 0x04,
};

/**
 * @brief Initialize an SPI-attached SX1278/RFM96 radio module
 *
 * @relates sx1278
 *
 * @param radio the sx1278 struct to initialize
 * @param spi the spi_module we are connecting through
 *
 * @return OOKRADIO_ERR_NONE if initialized successfully
 */
void sx1278_init(struct sx1278 *radio, struct spi_module *spi);

void sx1278_set_long_range_mode(struct sx1278 *radio, bool long_range_mode);
void sx1278_set_data_mode(struct sx1278 *radio, int mode);
void sx1278_set_modulation_type(struct sx1278 *radio, int modulation);
void sx1278_set_bit_sync_on(struct sx1278 *radio, bool bit_sync_on);
void sx1278_set_frequency(struct sx1278 *radio, int freq);
void sx1278_set_bitrate(struct sx1278 *radio, int bitrate);
void sx1278_set_rx_bandwidth(struct sx1278 *radio, int bw);
void sx1278_set_transmit_power(struct sx1278 *radio, int power, bool use_pa_boost);
void sx1278_set_mode(struct sx1278 *radio, int mode);

/**
 * @}
 */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SX1278_H