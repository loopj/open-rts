#ifndef RTS_RADIO_SX1278_H
#define RTS_RADIO_SX1278_H

#include <stdbool.h>

#include "spi_module.h"

struct sx1278 {
    struct spi_module *spi_module;
    bool use_pa_boost;
    int power;
    int mode;
};

// Oscillator
#define RFM95_FXOSC 32000000.0
#define RFM95_FSTEP (RFM95_FXOSC / 524288)

// Register map
enum {
    RFM95_REG_OP_MODE         = 0x01,
    RFM95_REG_BITRATE_MSB     = 0x02,
    RFM95_REG_BITRATE_LSB     = 0x03,
    RFM95_REG_FRF_MSB         = 0x06,
    RFM95_REG_FRF_MID         = 0x07,
    RFM95_REG_FRF_LSB         = 0x08,
    RFM95_REG_PA_CONFIG       = 0x09,
    RFM95_REG_PA_RAMP         = 0x0A,
    RFM95_REG_OCP             = 0x0B,
    RFM95_REG_RX_BW           = 0x12,
    RFM95_REG_OOK_PEAK        = 0x14,
    RFM95_REG_OOK_FIX         = 0x15,
    RFM95_REG_PACKET_CONFIG_2 = 0x31,
    RFM95_REG_IRQ_FLAGS_1     = 0x3E,
    RFM95_REG_DIO_MAPPING_1   = 0x40,
    RFM95_REG_PA_DAC          = 0x4D,
};

// RegOpMode (0x01)
enum {
    RFM95_LONG_RANGE_MODE        = 0x80,
    RFM95_LONG_RANGE_MODE_OFF    = 0x00,
    RFM95_LONG_RANGE_MODE_ON     = 0x80,
    RFM95_MODULATION_TYPE        = 0x60,
    RFM95_MODULATION_TYPE_FSK    = 0x00,
    RFM95_MODULATION_TYPE_OOK    = 0x20,
    RFM95_LOW_FREQUENCY_MODE     = 0x08,
    RFM95_LOW_FREQUENCY_MODE_OFF = 0x00,
    RFM95_LOW_FREQUENCY_MODE_ON  = 0x08,
    RFM95_MODE                   = 0x07,
    RFM95_MODE_SLEEP             = 0x00,
    RFM95_MODE_STDBY             = 0x01,
    RFM95_MODE_FSTX              = 0x02,
    RFM95_MODE_TX                = 0x03,
    RFM95_MODE_FSRX              = 0x04,
    RFM95_MODE_RX                = 0x05,
};

// RegPaConfig (0x09)
enum {
    RFM95_PA_SELECT          = 0x80,
    RFM95_PA_SELECT_RFO      = 0x00,
    RFM95_PA_SELECT_PA_BOOST = 0x80,
    RFM95_MAX_POWER          = 0x70,
    RFM95_MAX_POWER_MAX      = 0x70,
    RFM95_MAX_POWER_LOW      = 0x20,
    RFM95_OUTPUT_POWER       = 0x0F,
};

// RegRxBw (0x12)
enum {
    RFM95_RX_BW_MANT    = 0x18,
    RFM95_RX_BW_MANT_16 = 0x00,
    RFM95_RX_BW_MANT_20 = 0x08,
    RFM95_RX_BW_MANT_24 = 0x10,
    RFM95_RX_BW_EXP     = 0x07,
};

// RegOokPeak (0x14)
enum {
    RFM95_BIT_SYNC                = 0x20,
    RFM95_BIT_SYNC_ON             = 0x20,
    RFM95_BIT_SYNC_OFF            = 0x00,
    RFM95_OOK_THRESH_TYPE         = 0x18,
    RFM95_OOK_THRESH_TYPE_FIXED   = 0x00,
    RFM95_OOK_THRESH_TYPE_PEAK    = 0x08,
    RFM95_OOK_THRESH_TYPE_AVERAGE = 0x10,
};

// RegPacketConfig2 (0x31)
enum {
    RFM95_DATA_MODE            = 0x40,
    RFM95_DATA_MODE_CONTINUOUS = 0x00,
    RFM95_DATA_MODE_PACKET     = 0x40,
};

// RegIrqFlags1 (0x3E)
enum {
    RFM95_MODE_READY = 0x80,
};

// RegPaDac (0x4D)
enum {
    RFM95_PA_DAC          = 0x07,
    RFM95_PA_DAC_ENABLED  = 0x07,
    RFM95_PA_DAC_DISABLED = 0x04,
};

#ifdef __cplusplus
extern "C" {
#endif

void sx1278_init(struct sx1278 *radio, struct spi_module *spi,
                 bool use_pa_boost);
void sx1278_configure_for_rts(struct sx1278 *radio);
void sx1278_set_long_range_mode(struct sx1278 *radio, bool long_range_mode);
void sx1278_set_data_mode(struct sx1278 *radio, int mode);
void sx1278_set_modulation_type(struct sx1278 *radio, int modulation);
void sx1278_set_bit_sync_on(struct sx1278 *radio, bool bit_sync_on);
void sx1278_set_frequency(struct sx1278 *radio, int freq);
void sx1278_set_bitrate(struct sx1278 *radio, int bitrate);
void sx1278_set_rx_bandwidth(struct sx1278 *radio, int bw);
void sx1278_set_transmit_power(struct sx1278 *radio, int power);
void sx1278_set_mode(struct sx1278 *radio, int mode);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_RADIO_SX1278_H