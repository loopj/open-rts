#pragma once

#include <stdbool.h>

#include "hal/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rfm69_t {
    spi_module_t *spi_module;
    bool use_pa_boost;
    int power;
    int mode;
} rfm69_t;

void rfm69_init(rfm69_t *radio, spi_module_t *spi, bool use_pa_boost);
void rfm69_configure_for_rts(rfm69_t *radio);
void rfm69_set_data_mode(rfm69_t *radio, int mode);
void rfm69_set_modulation_type(rfm69_t *radio, int modulation);
void rfm69_set_frequency(rfm69_t *radio, int freq);
void rfm69_set_bitrate(rfm69_t *radio, int bitrate);
void rfm69_set_rx_bandwidth(rfm69_t *radio, int bw);
void rfm69_set_transmit_power(rfm69_t *radio, int power);
void rfm69_set_mode(rfm69_t *radio, int mode);

// Oscillator
#define RFM69_FXOSC 32000000.0
#define RFM69_FSTEP (RFM69_FXOSC / 524288)

// Registers
#define RFM69_REG_OP_MODE               0x01
#define RFM69_REG_DATA_MODUL            0x02
#define RFM69_REG_BITRATE_MSB           0x03
#define RFM69_REG_BITRATE_LSB           0x04
#define RFM69_REG_FRF_MSB               0x07
#define RFM69_REG_FRF_MID               0x08
#define RFM69_REG_FRF_LSB               0x09
#define RFM69_REG_PA_LEVEL              0x11
#define RFM69_REG_OCP                   0x13
#define RFM69_REG_RX_BW                 0x19
#define RFM69_REG_OOK_PEAK              0x1B
#define RFM69_REG_OOK_FIX               0x1D
#define RFM69_REG_IRQ_FLAGS_1           0x27
#define RFM69_REG_TEST_PA_1             0x5A
#define RFM69_REG_TEST_PA_2             0x5C

// RegOpMode                            0x01
#define RFM69_MODE                      0x1C
#define RFM69_MODE_SLEEP                0x00
#define RFM69_MODE_STDBY                0x04
#define RFM69_MODE_FS                   0x08
#define RFM69_MODE_TX                   0x0c
#define RFM69_MODE_RX                   0x10

// RegDataModul                         0x02
#define RFM69_DATA_MODE                 0x60
#define RFM69_DATA_MODE_PACKET          0x00
#define RFM69_DATA_MODE_CONTINUOUS_SYNC 0x40
#define RFM69_DATA_MODE_CONTINUOUS      0x60
#define RFM69_MODULATION_TYPE           0x08
#define RFM69_MODULATION_TYPE_FSK       0x00
#define RFM69_MODULATION_TYPE_OOK       0x08
#define RFM69_MODULATION_SHAPING        0x03
#define RFM69_MODULATION_SHAPING_NONE   0x00

// RegPaLevel                           0x11
#define RFM69_PA0_OFF                   0x00
#define RFM69_PA0_ON                    0x80
#define RFM69_PA1_OFF                   0x00
#define RFM69_PA1_ON                    0x40
#define RFM69_PA2_OFF                   0x00
#define RFM69_PA2_ON                    0x20
#define RFM69_OUTPUT_POWER              0x1F

// RegOcp                               0x13
#define RFM69_OCP_ON                    0x1A
#define RFM69_OCP_OFF                   0x0F

// RegRxBw                              0x19
#define RFM69_RX_BW_MANT                0x18
#define RFM69_RX_BW_MANT_16             0x00
#define RFM69_RX_BW_MANT_20             0x08
#define RFM69_RX_BW_MANT_24             0x10
#define RFM69_RX_BW_EXP                 0x07

#define RFM69_RXBW                      0x1F
#define RFM69_RXBW_1_3                  0x17
#define RFM69_RXBW_1_6                  0x0F
#define RFM69_RXBW_2_0                  0x07
#define RFM69_RXBW_2_6                  0x16
#define RFM69_RXBW_3_1                  0x0E
#define RFM69_RXBW_3_9                  0x06
#define RFM69_RXBW_5_2                  0x15
#define RFM69_RXBW_6_3                  0x0D
#define RFM69_RXBW_7_8                  0x05
#define RFM69_RXBW_10_4                 0x14
#define RFM69_RXBW_12_5                 0x0C
#define RFM69_RXBW_15_6                 0x04
#define RFM69_RXBW_20_8                 0x13
#define RFM69_RXBW_25                   0x0B
#define RFM69_RXBW_31_3                 0x03
#define RFM69_RXBW_41_7                 0x12
#define RFM69_RXBW_50                   0x0A
#define RFM69_RXBW_62_5                 0x02
#define RFM69_RXBW_83_3                 0x11
#define RFM69_RXBW_100                  0x09
#define RFM69_RXBW_125                  0x01
#define RFM69_RXBW_166_7                0x10
#define RFM69_RXBW_200                  0x08
#define RFM69_RXBW_250                  0x00

// RegOokPeak                           0x1B
#define RFM69_OOK_THRESH_TYPE           0xC0
#define RFM69_OOK_THRESH_TYPE_FIXED     0x00
#define RFM69_OOK_THRESH_TYPE_PEAK      0x40
#define RFM69_OOK_THRESH_TYPE_AVERAGE   0x80

// RegIrqFlags1                         0x27
#define RFM69_MODE_READY                0x80

// RegTestPa1                           0x5A
#define RFM69_TEST_PA_1_NORMAL          0x55
#define RFM69_TEST_PA_1_BOOST           0x5D

// RegTestPa2                           0x5C
#define RFM69_TEST_PA_2_NORMAL          0x70
#define RFM69_TEST_PA_2_BOOST           0x7C

#ifdef __cplusplus
} // extern "C"
#endif