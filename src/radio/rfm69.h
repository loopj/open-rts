#ifndef RTS_RADIO_RFM69_H
#define RTS_RADIO_RFM69_H

#include <stdbool.h>

#include "spi_module.h"

struct rfm69 {
    struct spi_module *spi_module;
    bool use_pa_boost;
    int power;
    int mode;
};

// Oscillator
#define RFM69_FXOSC 32000000.0
#define RFM69_FSTEP (RFM69_FXOSC / 524288)

// Register map
enum {
    RFM69_REG_OP_MODE     = 0x01,
    RFM69_REG_DATA_MODUL  = 0x02,
    RFM69_REG_BITRATE_MSB = 0x03,
    RFM69_REG_BITRATE_LSB = 0x04,
    RFM69_REG_FRF_MSB     = 0x07,
    RFM69_REG_FRF_MID     = 0x08,
    RFM69_REG_FRF_LSB     = 0x09,
    RFM69_REG_PA_LEVEL    = 0x11,
    RFM69_REG_OCP         = 0x13,
    RFM69_REG_RX_BW       = 0x19,
    RFM69_REG_OOK_PEAK    = 0x1B,
    RFM69_REG_OOK_FIX     = 0x1D,
    RFM69_REG_IRQ_FLAGS_1 = 0x27,
    RFM69_REG_TEST_PA_1   = 0x5A,
    RFM69_REG_TEST_PA_2   = 0x5C,
};

// RegOpMode (0x01)
enum {
    RFM69_MODE       = 0x1C,
    RFM69_MODE_SLEEP = 0x00,
    RFM69_MODE_STDBY = 0x04,
    RFM69_MODE_FS    = 0x08,
    RFM69_MODE_TX    = 0x0C,
    RFM69_MODE_RX    = 0x10,
};

// RegDataModul (0x02)
enum {
    RFM69_DATA_MODE                 = 0x60,
    RFM69_DATA_MODE_PACKET          = 0x00,
    RFM69_DATA_MODE_CONTINUOUS_SYNC = 0x40,
    RFM69_DATA_MODE_CONTINUOUS      = 0x60,
    RFM69_MODULATION_TYPE           = 0x08,
    RFM69_MODULATION_TYPE_FSK       = 0x00,
    RFM69_MODULATION_TYPE_OOK       = 0x08,
    RFM69_MODULATION_SHAPING        = 0x03,
    RFM69_MODULATION_SHAPING_NONE   = 0x00,
};

// RegPaLevel (0x11)
enum {
    RFM69_PA0_OFF      = 0x00,
    RFM69_PA0_ON       = 0x80,
    RFM69_PA1_OFF      = 0x00,
    RFM69_PA1_ON       = 0x40,
    RFM69_PA2_OFF      = 0x00,
    RFM69_PA2_ON       = 0x20,
    RFM69_OUTPUT_POWER = 0x1F,
};

// RegOcp (0x13)
enum {
    RFM69_OCP_ON  = 0x1A,
    RFM69_OCP_OFF = 0x0F,
};

// RegRxBw (0x19)
enum {
    RFM69_RX_BW_MANT    = 0x18,
    RFM69_RX_BW_MANT_16 = 0x00,
    RFM69_RX_BW_MANT_20 = 0x08,
    RFM69_RX_BW_MANT_24 = 0x10,
    RFM69_RX_BW_EXP     = 0x07,
};

enum {
    RFM69_RXBW       = 0x1F,
    RFM69_RXBW_1_3   = 0x17,
    RFM69_RXBW_1_6   = 0x0F,
    RFM69_RXBW_2_0   = 0x07,
    RFM69_RXBW_2_6   = 0x16,
    RFM69_RXBW_3_1   = 0x0E,
    RFM69_RXBW_3_9   = 0x06,
    RFM69_RXBW_5_2   = 0x15,
    RFM69_RXBW_6_3   = 0x0D,
    RFM69_RXBW_7_8   = 0x05,
    RFM69_RXBW_10_4  = 0x14,
    RFM69_RXBW_12_5  = 0x0C,
    RFM69_RXBW_15_6  = 0x04,
    RFM69_RXBW_20_8  = 0x13,
    RFM69_RXBW_25    = 0x0B,
    RFM69_RXBW_31_3  = 0x03,
    RFM69_RXBW_41_7  = 0x12,
    RFM69_RXBW_50    = 0x0A,
    RFM69_RXBW_62_5  = 0x02,
    RFM69_RXBW_83_3  = 0x11,
    RFM69_RXBW_100   = 0x09,
    RFM69_RXBW_125   = 0x01,
    RFM69_RXBW_166_7 = 0x10,
    RFM69_RXBW_200   = 0x08,
    RFM69_RXBW_250   = 0x00,
};

// RegOokPeak (0x1B)
enum {
    RFM69_OOK_THRESH_TYPE         = 0xC0,
    RFM69_OOK_THRESH_TYPE_FIXED   = 0x00,
    RFM69_OOK_THRESH_TYPE_PEAK    = 0x40,
    RFM69_OOK_THRESH_TYPE_AVERAGE = 0x80,
};

// RegIrqFlags1 (0x27)
enum {
    RFM69_MODE_READY = 0x80,
};

// RegTestPa1 (0x5A)
enum {
    RFM69_TEST_PA_1_NORMAL = 0x55,
    RFM69_TEST_PA_1_BOOST  = 0x5D,
};

// RegTestPa2 (0x5C)
enum {
    RFM69_TEST_PA_2_NORMAL = 0x70,
    RFM69_TEST_PA_2_BOOST  = 0x7C,
};

#ifdef __cplusplus
extern "C" {
#endif

void rfm69_init(struct rfm69 *radio, struct spi_module *spi, bool use_pa_boost);
void rfm69_configure_for_rts(struct rfm69 *radio);
void rfm69_set_data_mode(struct rfm69 *radio, uint8_t mode);
void rfm69_set_modulation_type(struct rfm69 *radio, uint8_t modulation);
void rfm69_set_frequency(struct rfm69 *radio, unsigned long freq);
void rfm69_set_bitrate(struct rfm69 *radio, uint16_t bitrate);
void rfm69_set_rx_bandwidth(struct rfm69 *radio, uint32_t bw);
void rfm69_set_transmit_power(struct rfm69 *radio, int8_t power);
void rfm69_set_mode(struct rfm69 *radio, uint8_t mode);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_RADIO_RFM69_H